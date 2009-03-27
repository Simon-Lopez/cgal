#include <Qt/qglobal.h>

#include <CGAL/AABB_tree/Plane_3_Bbox_3_do_intersect.h>
#include <CGAL/AABB_tree/Triangle_3_plane_3_intersection.h>
#include "Messages_interface.h"
#include "Scene_item_with_display_list.h"
#include "Scene_plane_item.h"
#include "Scene_polyhedron_item.h"
#include "Polyhedron_demo_plugin_interface.h"
#include <CGAL/gl.h>

#include <CGAL/bounding_box.h>

#include "Polyhedron_type.h"
#include <CGAL/AABB_tree/AABB_tree.h>
#include <CGAL/AABB_tree/Drawing_traits.h>

#include <QTime>

#include <QAction>
#include <QMainWindow>

typedef CGAL::Simple_cartesian<double> Simple_cartesian_kernel; 

typedef CGAL::AABB_tree<Simple_cartesian_kernel, 
                        Polyhedron::Facet_const_handle,
                        Polyhedron> AABB_tree;

class Q_DECL_EXPORT Scene_aabb_item : public Scene_item_with_display_list
{
  Q_OBJECT
public:
  Scene_aabb_item(const AABB_tree& tree_) : tree(tree_) {}

  bool isFinite() const { return true; }
  bool isEmpty() const { return tree.size() == 0; }
  Bbox bbox() const { 
    const CGAL::Bbox_3 bbox = tree.bbox();
    return Bbox(bbox.xmin(),
                bbox.ymin(),
                bbox.zmin(),
                bbox.xmax(),
                bbox.ymax(),
                bbox.zmax());
  }

  Scene_aabb_item* clone() const {
    return 0;
  }

  QString toolTip() const {
    return 
      tr("<p><b>%1</b> (mode: %2, color: %3)<br />"
         "<i>AABB_tree</i></p>"
         "<p>Number of nodes: %4</p>")
      .arg(this->name())
      .arg(this->renderingMode() == Wireframe ?
           "wireframe" :
           "fill")
      .arg(this->color().name())
      .arg(tree.size());
  }

  void direct_draw() const {
    CGAL::AABB::Drawing_traits traits;
    tree.traversal(0, traits);
  }

public:
  const AABB_tree& tree;
}; // end class Scene_aabb_item

class Q_DECL_EXPORT Scene_edges_item : public Scene_item
{
  Q_OBJECT
public:
  bool isFinite() const { return true; }
  bool isEmpty() const { return edges.empty(); }
  Bbox bbox() const { 
    if(isEmpty())
      return Bbox();
    CGAL::Bbox_3 bbox = edges.begin()->bbox();
    for(ssize_t i = 1, end = edges.size(); i < end; ++i) {
      bbox = bbox + edges[i].bbox();
    }
    return Bbox(bbox.xmin(),
                bbox.ymin(),
                bbox.zmin(),
                bbox.xmax(),
                bbox.ymax(),
                bbox.zmax());
  }

  Scene_edges_item* clone() const {
    Scene_edges_item* item = new Scene_edges_item;
    item->edges = edges;
    return item;
  }

  QString toolTip() const {
    return 
      tr("<p><b>%1</b> (mode: %2, color: %3)<br />"
         "<i>Edges</i></p>"
         "<p>Number of edges: %4</p>")
      .arg(this->name())
      .arg(this->renderingMode() == Wireframe ?
           "wireframe" :
           "fill")
      .arg(this->color().name())
      .arg(edges.size());
  }

  void draw() const {}

  void draw_edges() const {
    ::glBegin(GL_LINES);
    for(ssize_t i = 0, end = edges.size();
        i < end; ++i)
    {
      const Simple_cartesian_kernel::Point_3& a = edges[i].source();
      const Simple_cartesian_kernel::Point_3& b = edges[i].target();
      ::glVertex3d(a.x(), a.y(), a.z());
      ::glVertex3d(b.x(), b.y(), b.z());
    }
    ::glEnd();
  }

public:
  std::vector<Simple_cartesian_kernel::Segment_3> edges;
}; // end class Scene_edges_item


class Polyhedron_demo_cut_plugin : 
  public QObject,
  public Polyhedron_demo_plugin_interface
{
  Q_OBJECT
  Q_INTERFACES(Polyhedron_demo_plugin_interface);

public:
  Polyhedron_demo_cut_plugin() : QObject(), edges_item(0) {
  }

  void init(QMainWindow* mainWindow, Scene_interface* scene_interface,
            Messages_interface* m);
  QList<QAction*> actions() const;

public slots:
  void createCutPlane();
  void enableAction();
  void cut();
  void reset_edges() {
    edges_item = 0;
  }

private:
  Scene_interface* scene;
  Messages_interface* messages;
  Scene_plane_item* plane_item;
  Scene_edges_item* edges_item;
  QAction* actionCreateCutPlane;

  typedef std::map<QObject*,  AABB_tree> Trees;
  Trees trees;
}; // end Polyhedron_demo_cut_plugin

void Polyhedron_demo_cut_plugin::init(QMainWindow* mainWindow,
                                      Scene_interface* scene_interface,
                                      Messages_interface* m)
{
  scene = scene_interface;
  messages = m;
  actionCreateCutPlane = new QAction(tr("Create cutting plane"), mainWindow);
  connect(actionCreateCutPlane, SIGNAL(triggered()),
          this, SLOT(createCutPlane()));
}

QList<QAction*> Polyhedron_demo_cut_plugin::actions() const {
  return QList<QAction*>() << actionCreateCutPlane;
}

void Polyhedron_demo_cut_plugin::createCutPlane() {
  plane_item = new Scene_plane_item(scene);
  const Scene_interface::Bbox& bbox = scene->bbox();
  plane_item->setPosition((bbox.xmin+bbox.xmax)/2.f,
                          (bbox.ymin+bbox.ymax)/2.f,
                          (bbox.zmin+bbox.zmax)/2.f);
  connect(plane_item, SIGNAL(destroyed()),
          this, SLOT(enableAction()));
  plane_item->setManipulatable(true);
  plane_item->setClonable(false);
  plane_item->setColor(Qt::green);
  plane_item->setName(tr("Cutting plane"));
  connect(plane_item->manipulatedFrame(), SIGNAL(modified()),
          this, SLOT(cut()));
  scene->addItem(plane_item);
  actionCreateCutPlane->setEnabled(false);
}

void Polyhedron_demo_cut_plugin::cut() {
  if(!edges_item) {
    edges_item = new Scene_edges_item;
    edges_item->setName("Edges of the cut");
    edges_item->setColor(Qt::red);
    connect(edges_item, SIGNAL(destroyed()),
            this, SLOT(reset_edges()));
    scene->addItem(edges_item);
  }
  const qglviewer::Vec& pos = plane_item->manipulatedFrame()->position();
  const qglviewer::Vec& n = plane_item->manipulatedFrame()->orientation().axis(); 
  Simple_cartesian_kernel::Plane_3 plane(n[0], n[1],  n[2], - n * pos);
  edges_item->edges.clear();
  QTime time;
  time.start();
  for(size_t i = 0, end = scene->numberOfEntries(); i < end; ++i) {
    Scene_item* item = scene->item(i);
    Scene_polyhedron_item* poly_item = qobject_cast<Scene_polyhedron_item*>(item);
    if(!poly_item) continue;
    Trees::iterator it = trees.find(poly_item);
    if(it == trees.end()) {
      it = trees.insert(trees.begin(), std::make_pair(poly_item, AABB_tree()));
      it->second.build_faces(*poly_item->polyhedron());
      Scene_aabb_item* aabb_item = new Scene_aabb_item(it->second);
      aabb_item->setName(tr("AABB tree of %1").arg(poly_item->name()));
      aabb_item->setRenderingMode(Wireframe);
      scene->addItem(aabb_item);
      std::cerr << "size: " << it->second.size() << std::endl;
    }
    if(!CGAL::do_intersect(plane, it->second.bbox()))
      std::cerr << "no intersection\n";
    std::cerr << "all_intersection\n";
    it->second.all_intersection<Simple_cartesian_kernel::Segment_3>(plane, std::back_inserter(edges_item->edges));
  }
  messages->information(QString("cut (%1 ms). %2 edges.").arg(time.elapsed()).arg(edges_item->edges.size()));
  scene->itemChanged(edges_item);
}

void Polyhedron_demo_cut_plugin::enableAction() {
  actionCreateCutPlane->setEnabled(true);
}

Q_EXPORT_PLUGIN2(Polyhedron_demo_cut_plugin, Polyhedron_demo_cut_plugin);

#include "Polyhedron_demo_cut_plugin.moc"

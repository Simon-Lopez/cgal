// test for the linear_least_square_fitting() functions.


#include <CGAL/Cartesian.h>
#include <CGAL/copy_n.h>
#include <CGAL/linear_least_squares_fitting_2.h>
#include <CGAL/point_generators_2.h>

#include <vector>
#include <CGAL/Testsuite/assert.h>
#include <stdlib.h>
#define THRESHOLD 0.001
// types

typedef CGAL::Cartesian<double> Kernel;
typedef Kernel::FT FT;

typedef Kernel::Line_2 Line_2;
typedef Kernel::Point_2 Point_2;
typedef Kernel::Triangle_2   Triangle_2;
typedef Kernel::Iso_rectangle_2   Iso_rectangle_2;
typedef Kernel::Segment_2 Segment_2;
typedef Kernel::Vector_2 Vector_2;

// case with one rectangle in container vs it split into two triangles
// the fitting line must be the same.
void test_1()
{
  std::cout<<"Test 1"<<std::endl;
  std::list<Iso_rectangle_2> Iso_rectangles;
  Iso_rectangles.push_back(Iso_rectangle_2(Point_2(1.6,15.2),Point_2(11.6,19.2)));

  // fit a line
  // call all versions of the function
  std::cout << "fit 2D line to bigger rectangle...";
  Kernel k;
  Line_2 line;
  Point_2 centroid;
  FT quality;
  quality = linear_least_squares_fitting_2(Iso_rectangles.begin(),Iso_rectangles.end(),line,CGAL::PCA_dimension_2_tag());
  quality = linear_least_squares_fitting_2(Iso_rectangles.begin(),Iso_rectangles.end(),line,centroid,CGAL::PCA_dimension_2_tag());
  quality = linear_least_squares_fitting_2(Iso_rectangles.begin(),Iso_rectangles.end(),line,centroid,k,CGAL::PCA_dimension_2_tag());
  std::cout << "done (quality: " << quality << ") Line: " << line<<" centroid: "<<centroid<<std::endl;


  std::list<Triangle_2> Triangles1;
  Triangles1.push_back(Triangle_2(Point_2(1.6,15.2),Point_2(1.6,19.2),Point_2(11.6,19.2)));
  Triangles1.push_back(Triangle_2(Point_2(1.6,15.2),Point_2(11.6,19.2),Point_2(11.6,15.2)));

  // fit a line
  // call all versions of the function
  std::cout << "fit 2D line to two small triangles...";
  Kernel k1;
  Line_2 line1;
  Point_2 centroid1;
  FT quality1;
  quality1 = linear_least_squares_fitting_2(Triangles1.begin(),Triangles1.end(),line1,CGAL::PCA_dimension_2_tag());
  quality1 = linear_least_squares_fitting_2(Triangles1.begin(),Triangles1.end(),line1,centroid1,CGAL::PCA_dimension_2_tag());
  quality1 = linear_least_squares_fitting_2(Triangles1.begin(),Triangles1.end(),line1,centroid1,k1,CGAL::PCA_dimension_2_tag());
  std::cout << "done (quality: " << quality1 << ") Line: " << line1<<" centroid: "<<centroid1<<std::endl;

  
  if(!(std::abs(-1.0*line.a()/line.b() - -1.0*line1.a()/line1.b()) <= THRESHOLD && std::abs(line.c()/line.b() - line1.c()/line1.b()) <= THRESHOLD && std::abs(quality1 - quality) <= THRESHOLD))
  {
    std::cout << "failure" << std::endl;
    exit(1); // failure
  }
}

// case with one rectangle in container vs it split into four triangles
// the fitting line must be the same.
void test_2()
{
  std::cout<<"Test 2"<<std::endl;
  std::list<Iso_rectangle_2> Iso_rectangles;
  Iso_rectangles.push_back(Iso_rectangle_2(Point_2(1.6,15.2),Point_2(11.6,19.2)));

  // fit a line
  // call all versions of the function
  std::cout << "fit 2D line to bigger rectangle...";
  Kernel k;
  Line_2 line;
  Point_2 centroid;
  FT quality;
  quality = linear_least_squares_fitting_2(Iso_rectangles.begin(),Iso_rectangles.end(),line,CGAL::PCA_dimension_2_tag());
  quality = linear_least_squares_fitting_2(Iso_rectangles.begin(),Iso_rectangles.end(),line,centroid,CGAL::PCA_dimension_2_tag());
  quality = linear_least_squares_fitting_2(Iso_rectangles.begin(),Iso_rectangles.end(),line,centroid,k,CGAL::PCA_dimension_2_tag());
  std::cout << "done (quality: " << quality << ") Line: " << line<<" centroid: "<<centroid<<std::endl;


  std::list<Triangle_2> Triangles1;
  Triangles1.push_back(Triangle_2(Point_2(1.6,15.2),Point_2(1.6,19.2),Point_2(6.6,17.2)));
  Triangles1.push_back(Triangle_2(Point_2(11.6,19.2),Point_2(11.6,15.2),Point_2(6.6,17.2)));
  Triangles1.push_back(Triangle_2(Point_2(1.6,19.2),Point_2(11.6,19.2),Point_2(6.6,17.2)));
  Triangles1.push_back(Triangle_2(Point_2(1.6,15.2),Point_2(11.6,15.2),Point_2(6.6,17.2)));

  // fit a line
  // call all versions of the function
  std::cout << "fit 2D line to four small triangles...";
  Kernel k1;
  Line_2 line1;
  Point_2 centroid1;
  FT quality1;
  quality1 = linear_least_squares_fitting_2(Triangles1.begin(),Triangles1.end(),line1,CGAL::PCA_dimension_2_tag());
  quality1 = linear_least_squares_fitting_2(Triangles1.begin(),Triangles1.end(),line1,centroid1,CGAL::PCA_dimension_2_tag());
  quality1 = linear_least_squares_fitting_2(Triangles1.begin(),Triangles1.end(),line1,centroid1,k1,CGAL::PCA_dimension_2_tag());
  std::cout << "done (quality: " << quality1 << ") Line: " << line1<<" centroid: "<<centroid1<<std::endl;

  
  if(!(std::abs(-1.0*line.a()/line.b() - -1.0*line1.a()/line1.b()) <= THRESHOLD && std::abs(line.c()/line.b() - line1.c()/line1.b()) <= THRESHOLD && std::abs(quality1 - quality) <= THRESHOLD))
  {
    std::cout << "failure" << std::endl;
    exit(1); // failure
  }
}

int main()
{
  std::cout << "Test 2D linear_least_squares_fitting_triangles"  << std::endl;

  test_1();
  test_2();

  return 0; // success
}

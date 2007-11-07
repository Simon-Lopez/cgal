// Copyright (c) 2005-2006  INRIA Sophia-Antipolis (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// Partially supported by the IST Programme of the EU as a Shared-cost
// RTD (FET Open) Project under Contract No  IST-2000-26473 
// (ECG - Effective Computational Geometry for Curves and Surfaces) 
// and a STREP (FET Open) Project under Contract No  IST-006413 
// (ACS -- Algorithms for Complex Shapes)
//
// $URL$
// $Id$
//
// Author(s) : Monique Teillaud <Monique.Teillaud@sophia.inria.fr>
//             Sylvain Pion     <Sylvain.Pion@sophia.inria.fr>
//             Pedro Machado    <tashimir@gmail.com>

template <class SK>
void _test_spherical_kernel_compute(SK sk)
{
  typedef typename SK::RT                                          RT;
  typedef typename SK::FT                                          FT;
  typedef typename SK::Root_of_2                                   Root_of_2;
  typedef typename SK::Circular_arc_point_3                        Circular_arc_point_3;
  typedef typename SK::Circular_arc_3                              Circular_arc_3;
  typedef typename SK::Point_3                                     Point_3;
  typedef typename SK::Plane_3                                     Plane_3;
  typedef typename SK::Circle_3                                    Circle_3;
  typedef typename SK::Sphere_3                                    Sphere_3;
  typedef typename SK::Algebraic_kernel                            AK;
  typedef typename SK::Get_equation                                Get_equation;
  typedef typename SK::Equal_3                                     Equal_3;
  typedef typename SK::Construct_circle_3                          Construct_circle_3;
  typedef typename SK::Construct_sphere_3                          Construct_sphere_3;
  typedef typename SK::Construct_circular_arc_3                    Construct_circular_arc_3;
  typedef typename SK::Construct_circular_arc_point_3              Construct_circular_arc_point_3;
  typedef typename SK::Compute_area_divided_by_pi_3                  Compute_area_divided_by_pi_3;
  typedef typename SK::Compute_squared_length_divided_by_pi_square_3 Compute_squared_length_divided_by_pi_square_3;
  typedef typename SK::Compute_approximate_area_3                    Compute_approximate_area_3;
  typedef typename SK::Compute_approximate_squared_length_3         Compute_approximate_squared_length_3;
  typedef typename SK::Compute_approximate_angle_3                   Compute_approximate_angle_3;
  typedef typename SK::Polynomials_for_circle_3                    Polynomials_for_circle_3;
  typedef typename AK::Polynomial_for_spheres_2_3                  Polynomial_for_spheres_2_3;
  typedef typename AK::Polynomial_1_3                              Polynomial_1_3;
  typedef typename AK::Polynomials_for_line_3                      Polynomials_for_line_3;
  typedef typename AK::Root_for_spheres_2_3                        Root_for_spheres_2_3;

  std::cout << "TESTING COMPUTATIONS" << std::endl;

  Equal_3 theEqual_3 = sk.equal_3_object();
  Get_equation theGet_equation = sk.get_equation_object();
  Construct_circle_3 theConstruct_circle_3 = sk.construct_circle_3_object();
  Construct_sphere_3 theConstruct_sphere_3 = sk.construct_sphere_3_object();
  Construct_circular_arc_3 theConstruct_circular_arc_3 = sk.construct_circular_arc_3_object();
  Construct_circular_arc_point_3 theConstruct_circular_arc_point_3 = sk.construct_circular_arc_point_3_object();
  Compute_area_divided_by_pi_3 theCompute_area_divided_by_pi_3 = sk.compute_area_divided_by_pi_3_object();
  Compute_squared_length_divided_by_pi_square_3 theCompute_squared_length_divided_by_pi_square_3 = 
    sk.compute_squared_length_divided_by_pi_square_3_object();
  Compute_approximate_area_3 theCompute_approximate_area_3 = sk.compute_approximate_area_3_object();
  Compute_approximate_squared_length_3 theCompute_approximate_squared_length_3 = 
    sk.compute_approximate_squared_length_3_object();
  Compute_approximate_angle_3 theCompute_approximate_angle_3 = sk.compute_approximate_angle_3_object();

  CGAL::Random generatorOfgenerator;
  int random_seed = generatorOfgenerator.get_int(0, 123456);
  CGAL::Random theRandom(random_seed);
  int random_max = 5;
  int random_min = -5; 

  std::cout << "Testing Approximate_area of a Circle_3" << std::endl;
  std::cout << "Testing Compute_area_divided_by_pi  of a Circle_3" << std::endl;
  std::cout << "Testing Approximate_squared_length of a Circle_3" << std::endl;
  std::cout << "Testing Compute_squared_length_divided_by_pi_square of a Circle_3" << std::endl;

  for(int i=0; i<400; i++) {
    Circle_3 circle[2];
    for(int j=0; j<2; j++) {
      int a,b,c,d,u,v,r;
      FT x,y,z;
      do {
        a = theRandom.get_int(random_min,random_max);
        b = theRandom.get_int(random_min,random_max);
        c = theRandom.get_int(random_min,random_max);
        d = theRandom.get_int(random_min,random_max);
      } while((a == 0) && (b == 0) && (c == 0));
      u = theRandom.get_int(random_min,random_max);
      v = theRandom.get_int(random_min,random_max);
      do {
        r = theRandom.get_int(random_min,random_max);
      } while(r <= 0);
      if(a != 0) {
        x = FT_Q(-(b*u + c*v + d),a);
        y = FT(u);
        z = FT(v);
      } else if(b != 0) {
        x = FT(u);
        y = FT_Q(-(a*u + c*v + d),b);
        z = FT(v);
      } else {
        x = FT(u);
        y = FT(v);
        z = FT_Q(-(a*u + b*v + d),c);
      } 
      const Plane_3 plane = Plane_3(a,b,c,d);
      const FT sqr = FT(r*r);
      const Point_3 p = Point_3(x,y,z);
      circle[j] = theConstruct_circle_3(p,sqr,plane);
      const FT ardp = theCompute_area_divided_by_pi_3(circle[j]);
      const FT sldps = theCompute_squared_length_divided_by_pi_square_3(circle[j]);
      CGAL_test_assert(ardp == r*r);
      CGAL_test_assert(sldps == 4*r*r);
    }
    const double ar1 = theCompute_approximate_area_3(circle[0]);
    const FT ardp1 = theCompute_area_divided_by_pi_3(circle[0]);
    const double asl1 = theCompute_approximate_squared_length_3(circle[0]);
    const FT sldps1 = theCompute_squared_length_divided_by_pi_square_3(circle[0]);
    const double ar2 = theCompute_approximate_area_3(circle[1]);
    const FT ardp2 = theCompute_area_divided_by_pi_3(circle[1]);
    const double asl2 = theCompute_approximate_squared_length_3(circle[1]);
    const FT sldps2 = theCompute_squared_length_divided_by_pi_square_3(circle[1]);
    if(circle[0].squared_radius() > circle[1].squared_radius()) {
      CGAL_test_assert(ar1 > ar2); CGAL_test_assert(ardp1 > ardp2);
      CGAL_test_assert(asl1 > asl2); CGAL_test_assert(sldps1 > sldps2);
    } else if(circle[0].squared_radius() == circle[1].squared_radius()) {
      CGAL_test_assert(ar1 == ar2); CGAL_test_assert(ardp1 == ardp2);
      CGAL_test_assert(asl1 == asl2); CGAL_test_assert(sldps1 == sldps2);
    } else {
      CGAL_test_assert(ar1 < ar2); CGAL_test_assert(ardp1 < ardp2);
      CGAL_test_assert(asl1 < asl2); CGAL_test_assert(sldps1 < sldps2);
    } 
  }

  std::cout << "Testing Approximate_angle of a Circular_arc_3" << std::endl;
  std::cout << "Testing Approximate_squared_length of a Circular_arc_3" << std::endl;

  Root_for_spheres_2_3 rt[8];

  rt[0] = Root_for_spheres_2_3(0,1,0);
  rt[1] = Root_for_spheres_2_3(CGAL::make_root_of_2(FT(0),-FT(FT_Q(1,2)),FT(2)), CGAL::make_root_of_2(FT(0),FT(FT_Q(1,2)),FT(2)),0);
  rt[2] = Root_for_spheres_2_3(-1,0,0);
  rt[3] = Root_for_spheres_2_3(CGAL::make_root_of_2(FT(0),-FT(FT_Q(1,2)),FT(2)), CGAL::make_root_of_2(FT(0),-FT(FT_Q(1,2)),FT(2)),0);
  rt[4] = Root_for_spheres_2_3(0,-1,0);
  rt[5] = Root_for_spheres_2_3(CGAL::make_root_of_2(FT(0),FT(FT_Q(1,2)),FT(2)), CGAL::make_root_of_2(FT(0),-FT(FT_Q(1,2)),FT(2)),0);
  rt[6] = Root_for_spheres_2_3(1,0,0);
  rt[7] = Root_for_spheres_2_3(CGAL::make_root_of_2(FT(0),FT(FT_Q(1,2)),FT(2)), CGAL::make_root_of_2(FT(0),FT(FT_Q(1,2)),FT(2)),0);

  Circular_arc_point_3 cp[8]; 
  for(int i=0; i<8; i++) {
    cp[i] = theConstruct_circular_arc_point_3(rt[i]);
  }

  const double pi = std::acos(-1.);

  const Polynomials_for_circle_3 pcc_test = 
      std::make_pair(Polynomial_for_spheres_2_3(0,0,0,1),
                     Polynomial_1_3(0,0,1,0));
  Circle_3 cc = theConstruct_circle_3(pcc_test);
  for(int i=0; i<8; i++) {
    for(int j=i+1; j<8; j++) {
      Circular_arc_3 ca = theConstruct_circular_arc_3(cc,cp[i],cp[j]);
      Circular_arc_3 cb = theConstruct_circular_arc_3(cc,cp[j],cp[i]);
      const double num = (double) (j-i);
      const double ang1 = (pi/4.0) * num;
      const double ang2 = 2*pi - ang1;
      const double app_ang1 = theCompute_approximate_angle_3(ca);
      const double app_ang2 = theCompute_approximate_angle_3(cb);
      const double v1 = app_ang1 - ang1;
      const double v2 = app_ang2 - ang2;
      const double diff1 = ((v1 > 0) ? (v1) : (-v1));
      const double diff2 = ((v2 > 0) ? (v2) : (-v2));
      // we suppose at least a precision of 10e-8, but it is not necessarily true
      CGAL_test_assert(diff1 < 10e-8);
      CGAL_test_assert(diff2 < 10e-8);

      const double sql1 = ang1 * ang1;
      const double sql2 = ang2 * ang2;
      const double app_sql1 = theCompute_approximate_squared_length_3(ca);
      const double app_sql2 = theCompute_approximate_squared_length_3(cb);
      const double vv1 = app_sql1 - sql1;
      const double vv2 = app_sql2 - sql2;
      const double diffv1 = ((vv1 > 0) ? (vv1) : (-vv1));
      const double diffv2 = ((vv2 > 0) ? (vv2) : (-vv2));
      // we suppose at least a precision of 10e-8, but it is not necessarily true
      CGAL_warning(diffv1 < 10e-8);
      CGAL_warning(diffv2 < 10e-8);
    }
  }

  std::cout << "All tests on computations are OK." << std::endl;
}

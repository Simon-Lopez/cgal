// Copyright (c) 1999  Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbruecken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).  All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL$
// $Id$
// 
//
// Author(s)     : Stefan Schirra
 

#ifndef CGAL__TEST_FCT_POINT_3_H
#define CGAL__TEST_FCT_POINT_3_H

template <class R>
bool
_test_fct_point_3(const R& )
{
 std::cout << "Testing functions Point_3" ;

 typedef typename  R::RT    RT;
 typedef typename  R::FT    FT;

 CGAL::Point_3<R> p1(RT(18), RT(15), RT(-21), RT(3) ); // 6,5,-7
 CGAL::Point_3<R> p2(RT(18), RT(15), RT( 12), RT(3) ); // 6,5,4
 CGAL::Point_3<R> p3(RT(18), RT(12), RT(-21), RT(3) ); // 6,4,-7
 CGAL::Point_3<R> p4(RT(28), RT(40), RT( 20), RT(4) ); // 7,10,5
 CGAL::Point_3<R> p5(RT(12), RT(-4), RT(-20), RT(4) ); // 3,-1,-5

 CGAL_test_assert( CGAL::compare_xyz(p1,p2) == CGAL::SMALLER );
 CGAL_test_assert( CGAL::compare_xyz(p3,p2) == CGAL::SMALLER );
 CGAL_test_assert( CGAL::compare_xyz(p3,p1) == CGAL::SMALLER );
 CGAL_test_assert( CGAL::compare_xyz(p3,p2) == CGAL::SMALLER );
 CGAL_test_assert( CGAL::compare_xyz(p2,p1) == CGAL::LARGER );
 CGAL_test_assert( CGAL::compare_xyz(p2,p3) == CGAL::LARGER );
 CGAL_test_assert( CGAL::compare_xyz(p4,p3) == CGAL::LARGER );
 CGAL_test_assert( CGAL::compare_xyz(p4,p4) == CGAL::EQUAL );

 CGAL_test_assert( CGAL::lexicographically_xyz_smaller_or_equal(p1,p1) );
 CGAL_test_assert( CGAL::lexicographically_xyz_smaller_or_equal(p3,p1) );
 CGAL_test_assert( CGAL::lexicographically_xyz_smaller_or_equal(p3,p2) );
 CGAL_test_assert( CGAL::lexicographically_xyz_smaller_or_equal(p3,p4) );

 CGAL_test_assert( !CGAL::lexicographically_xyz_smaller(p3,p3) );
 CGAL_test_assert( CGAL::lexicographically_xyz_smaller(p3,p2) );
 CGAL_test_assert( !CGAL::lexicographically_xyz_smaller(p4,p3) );

 CGAL_test_assert( CGAL::compare_x(p2,p3) == CGAL::EQUAL );
 CGAL_test_assert( CGAL::compare_x(p2,p4) == CGAL::SMALLER );
 CGAL_test_assert( CGAL::compare_x(p4,p5) == CGAL::LARGER );
 CGAL_test_assert( CGAL::compare_y(p2,p1) == CGAL::EQUAL );
 CGAL_test_assert( CGAL::compare_y(p3,p2) == CGAL::SMALLER );
 CGAL_test_assert( CGAL::compare_y(p4,p5) == CGAL::LARGER );
 CGAL_test_assert( CGAL::compare_x(p1,p3) == CGAL::EQUAL );
 CGAL_test_assert( CGAL::compare_x(p2,p4) == CGAL::SMALLER );
 CGAL_test_assert( CGAL::compare_x(p4,p5) == CGAL::LARGER );

 CGAL_test_assert( CGAL::x_equal(p1,p1) );
 CGAL_test_assert( CGAL::x_equal(p2,p3) );
 CGAL_test_assert( !CGAL::x_equal(p2,p4) );

 CGAL_test_assert( CGAL::y_equal(p1,p2) );
 CGAL_test_assert( !CGAL::y_equal(p1,p3) );

 CGAL_test_assert( CGAL::z_equal(p1,p3) );
 CGAL_test_assert( !CGAL::z_equal(p4,p5) );

 std::cout <<'.';

 CGAL::Point_3<R> p6 ( RT(6), RT(4), RT(7) );
 CGAL_test_assert( CGAL::coplanar( p1, p2, p3, p6) );
 CGAL_test_assert( CGAL::coplanar( p1, p1, p3, p4) );
 CGAL_test_assert( CGAL::coplanar( p4, p1, p5, p5 + (p4-p1) ) );
 CGAL_test_assert( !CGAL::coplanar( p4, p1, p2, p3 ) );

 CGAL_test_assert( !CGAL::collinear( p1, p2, p3 ) );
 CGAL_test_assert( CGAL::collinear( p1, p2, p2 + (p2-p1) ) );

 // ordered: arg1 - arg2 - arg3
 CGAL_test_assert( CGAL::are_ordered_along_line( p1, p2, p2 + (p2-p1)) );
 CGAL_test_assert( CGAL::are_ordered_along_line( p1, p2, p2) );
 CGAL_test_assert( !CGAL::are_ordered_along_line( p1, p2 + (p2-p1), p2) );
 CGAL_test_assert( !CGAL::are_ordered_along_line( p1, p5, p2 ) );
 CGAL_test_assert( CGAL::are_ordered_along_line( p2, p2, p2) );

 CGAL_test_assert( CGAL::collinear_are_ordered_along_line( p1, p2, p2 + (p2-p1)) );
 CGAL_test_assert( !CGAL::collinear_are_ordered_along_line( p1, p2 + (p2-p1), p2) );

 CGAL_test_assert( CGAL::collinear_are_ordered_along_line( p1, p1, p1));
 CGAL_test_assert( !CGAL::collinear_are_ordered_along_line( p1, p4, p1));
 CGAL_test_assert( !CGAL::collinear_are_ordered_along_line( p1, p3, p1));

 // strictly ordered: ordered && args pairwise distinct
 CGAL_test_assert( CGAL::are_strictly_ordered_along_line( p1, p2, p2 + (p2-p1)) );
 CGAL_test_assert( !CGAL::are_strictly_ordered_along_line( p1, p2, p2) );
 CGAL_test_assert( !CGAL::are_strictly_ordered_along_line( p1, p2 + (p2-p1), p2) );
 CGAL_test_assert( !CGAL::are_strictly_ordered_along_line( p1, p5, p2 ) );
 CGAL_test_assert( !CGAL::are_strictly_ordered_along_line( p2, p2, p2) );

 CGAL_test_assert( CGAL::collinear_are_strictly_ordered_along_line(p1, p2, p2 + (p2-p1)));
 CGAL_test_assert( !CGAL::collinear_are_strictly_ordered_along_line(p1, p2, p2));
 CGAL_test_assert( !CGAL::collinear_are_strictly_ordered_along_line(p1, p2 + (p2-p1), p2));
 CGAL_test_assert( !CGAL::collinear_are_strictly_ordered_along_line(p1, p1, p1));
 CGAL_test_assert( !CGAL::collinear_are_strictly_ordered_along_line(p1, p4, p1));

 CGAL_test_assert( CGAL::collinear( p3, p2, p3 ) );
 CGAL_test_assert( CGAL::collinear( p2, p2, p3 ) );
 CGAL_test_assert( CGAL::collinear( p2, p3, p3 ) );

 std::cout << '.';

 CGAL::Point_3<R> pe0( RT(1), RT(0), RT(0) );
 CGAL::Point_3<R> pe1( RT(0), RT(1), RT(0) );
 CGAL::Point_3<R> pe2( RT(0), RT(0), RT(1) );

 CGAL_test_assert( CGAL::orientation( CGAL::Point_3<R>(CGAL::ORIGIN), pe0, pe1, pe2 ) \
                           == CGAL::POSITIVE);

 CGAL_test_assert( CGAL::orientation( p1, p2, p3, p6 ) == CGAL::ZERO );

 CGAL::Point_3<R> p7( RT(-8), RT(0), RT(0), RT(-2) );
 CGAL::Point_3<R> p8( RT(8), RT(4), RT(0), RT(2) );
 CGAL::Point_3<R> p9( RT(0), RT(12), RT(0), RT(4) );

 CGAL_test_assert( CGAL::orientation( p7, p8, p9, p4) == CGAL::POSITIVE );
 CGAL_test_assert( CGAL::orientation( p7, p9, p8, p5) == CGAL::POSITIVE );
 CGAL_test_assert( CGAL::orientation( p7, p8, p9, p5) == CGAL::NEGATIVE );
 CGAL_test_assert( CGAL::orientation( p8, p7, p9, p4) == CGAL::NEGATIVE );

 std::cout <<'.';

 CGAL::Point_3<R> p10( RT(0), RT(0), RT(16), RT(8) );

// CGAL::side_of_bounded_sphere()
 CGAL_test_assert( CGAL::side_of_bounded_sphere(p7,p8,p9,p10,p1) ==CGAL::ON_UNBOUNDED_SIDE);
 CGAL_test_assert( CGAL::side_of_bounded_sphere(p7,p9,p8,p10,p1) ==CGAL::ON_UNBOUNDED_SIDE);
 CGAL::Point_3<R> p0(CGAL::ORIGIN);
 CGAL_test_assert( CGAL::side_of_bounded_sphere(p7,p8,p9,p10,p0) ==CGAL::ON_BOUNDED_SIDE);
 CGAL::Vector_3<R> v001( RT(0), RT(0), RT(1) );
 CGAL::Vector_3<R> v010( RT(0), RT(1), RT(0) );
 CGAL::Vector_3<R> v100( RT(1), RT(0), RT(0) );
 CGAL_test_assert( CGAL::side_of_bounded_sphere(p3 + v001, p3-v001, p3+v010, p3-v100, \
                                      p3 - v010) == CGAL::ON_BOUNDARY );
// CGAL::side_of_bounded_sphere() is further tested in
// _test_fct_points_implicit_sphere(const R& )

 CGAL_test_assert( CGAL::compare_distance_to_point(p3, p3 + v001, p3+v010) == 
                                                        CGAL::EQUAL );
 CGAL_test_assert( CGAL::compare_distance_to_point(p0, p1, p2) == CGAL::LARGER );
 CGAL_test_assert( CGAL::compare_distance_to_point(p0, p3, p1) == CGAL::SMALLER );
 CGAL_test_assert( CGAL::compare_distance_to_point(p1, p3, p5) == CGAL::SMALLER );
 CGAL_test_assert( CGAL::has_larger_distance_to_point(p0, p1, p2) );
 CGAL_test_assert( CGAL::has_larger_distance_to_point(p3, p5, p1) );
 CGAL_test_assert( CGAL::has_smaller_distance_to_point(p0, p2, p1) );
 CGAL_test_assert( CGAL::has_smaller_distance_to_point(p3, p1, p5) );

 CGAL_test_assert( CGAL::compare_squared_distance(p3, p3 + v001, CGAL::squared_distance(p3+v010,p3)) == 
                                                        CGAL::EQUAL );
 CGAL_test_assert( CGAL::compare_squared_distance(p0, p1, CGAL::squared_distance(p2,p0)) == CGAL::LARGER );
 CGAL_test_assert( CGAL::compare_squared_distance(p0, p3, CGAL::squared_distance(p1,p0)) == CGAL::SMALLER );
 CGAL_test_assert( CGAL::compare_squared_distance(p1, p3, CGAL::squared_distance(p5,p1)) == CGAL::SMALLER );

 std::cout << "done" << std::endl;
 return true;
}
#endif // CGAL__TEST_FCT_POINT_3_H

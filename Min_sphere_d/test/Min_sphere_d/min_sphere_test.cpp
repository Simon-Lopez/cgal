// ============================================================================
//
// Copyright (c) 1997 The CGAL Consortium
//
// This software and related documentation is part of an INTERNAL release
// of the Computational Geometry Algorithms Library (CGAL). It is not
// intended for general use.
//
// ----------------------------------------------------------------------------
//
// release       : $CGAL_Revision: CGAL-wip $
// release_date  : $CGAL_Date$
//
// chapter       : $CGAL_Chapter: Optimisation $
// package       : $CGAL_Package: MinSphere $
// file          : min_sphere_test.C
// source        : web/Optimisation/Min_sphere_d.aw
// revision      : $Id$
// revision_date : $Date$
// author(s)     : Sven Sch�nherr <sven@inf.fu-berlin.de>
//                 Bernd G�rtner
//
// coordinator   : ETH Zurich (Bernd G�rtner <gaertner@inf.ethz.ch>)
//
// implementation: dD Smallest Enclosing Sphere
// ============================================================================
// hack to overcome internal compiler error of egcs
#define FT_(x) FT(x,1)
#define RT_(x) RT(x,1)

// hack to overcome external linkage conflict warning in MIPS
#define __SGI_STL_INTERNAL_RELOPS

#include<CGAL/basic.h>

#include <CGAL/Random.h>
#include <CGAL/Cartesian_d.h>
#include <CGAL/Homogeneous_d.h>
#include <sstream>
#include <CGAL/Testsuite/assert.h>
#include <CGAL/Min_sphere_annulus_d_traits_d.h>
#include <CGAL/Min_sphere_d.h>
#include <CGAL/Gmpq.h>

using namespace CGAL;

typedef Gmpq                                NT;
typedef NT                                  FT;
typedef NT                                  RT;
typedef Cartesian_d<FT>                     C;
typedef Homogeneous_d<RT>                   H;
typedef Min_sphere_annulus_d_traits_d<C>    Cartesian_traits;
typedef Min_sphere_annulus_d_traits_d<H>    Homogeneous_traits;
typedef Min_sphere_d<Cartesian_traits>      Min_sphereC;
typedef Min_sphere_d<Homogeneous_traits>    Min_sphereH;
typedef Point_d<C>                          PointC;
typedef Point_d<H>                          PointH;


// checked traits
Cartesian_traits                                    tC;
Homogeneous_traits                                  tH;

const int n = 10;                           // number of points
const int D = 2;                            // dimension of points
const int r = 128;                          // coordinate range
bool verbose = true;

// NT == Quotient<NT> ?
bool equals (NT x, Quotient<NT> y)
{
    return (Quotient<NT>(x) == y);
}

// PointC == Point H ?
bool equals (PointC p, PointH q)
{
    int dim =  p.dimension();
    if (q.dimension() != dim) return false;
    for (int j=0; j<dim; ++j)
       if (!equals(p.cartesian(j),q.cartesian(j)))
            return false;
    return true;
}




int main ()
{
    Point_d<C>  PC[n];          // cartesian point set
    Point_d<H>  PH[n];          // homogeneous point set
    int         coord[D];       // arrays for random coordinates
    FT          coordC[D];      // ... cartesian version
    RT          coordH[D+1];    // ... homogeneous version
    Random      my_random;      // random number generator
    
    
    for (int i=0; i<n; ++i) {
        int j;
        // random coordinates
        for (j=0; j<D; ++j)
            coord[j] = my_random (r);
    
        // cartesian point
        for (j=0; j<D; ++j)
            coordC[j] = FT (coord[j]);
        PC[i] = Point_d<C>(D, coordC, coordC+D);
    
        // homogeneous point
        for (j=0; j<D; ++j)
            coordH[j] = RT(2*coord[j]);
        coordH[D] = RT(2);
        PH[i] = Point_d<H>(D, coordH, coordH+D+1);
    }
    
    
    // test constructors
    
    // default
    #ifdef __BORLANDC__
    // problems with default traits argument in constructor calls
    Min_sphereC         msC_empty(tC); CGAL_test_assert(msC_empty.is_valid(verbose));
    Min_sphereH         msH_empty(tH); CGAL_test_assert(msH_empty.is_valid(verbose));
    #else
    Min_sphereC         msC_empty; CGAL_test_assert(msC_empty.is_valid(verbose));
    Min_sphereH         msH_empty; CGAL_test_assert(msH_empty.is_valid(verbose));
    #endif
    
    // from range
    Min_sphereC         msC (PC, PC+n, tC); CGAL_test_assert(msC.is_valid(verbose));
    Min_sphereH         msH (PH, PH+n, tH); CGAL_test_assert(msH.is_valid(verbose));
    
    // copy
    Min_sphereC         msC1 (msC); CGAL_test_assert(msC1.is_valid(verbose));
    Min_sphereH         msH1 (msH); CGAL_test_assert(msH1.is_valid(verbose));
    
    PointC              centerC (msC.center()), centerC1 (msC1.center());
    PointH              centerH (msH.center()), centerH1 (msH1.center());
    
    FT                  radiusC (msC.squared_radius()),
                        radiusC1 (msC1.squared_radius());
    Quotient<RT>        radiusH (msH.squared_radius()),
                        radiusH1 (msH1.squared_radius());
    
    CGAL_test_assert(equals (centerC, centerH));
    CGAL_test_assert(centerC == centerC1); CGAL_test_assert(centerH == centerH1);
    CGAL_test_assert(equals (radiusC, radiusH));
    CGAL_test_assert(radiusC == radiusC1); CGAL_test_assert(radiusH == radiusH1);
    
    // assignment
    msC1 = msC; msH1 = msH;
    CGAL_test_assert(centerC == centerC1); CGAL_test_assert(centerH == centerH1);
    CGAL_test_assert(radiusC == radiusC1); CGAL_test_assert(radiusH == radiusH1);
    
    
    // test set method
    msC.set (PC, PC+n); CGAL_test_assert(msC.is_valid(verbose));
    msH.set (PH, PH+n); CGAL_test_assert(msH.is_valid(verbose));
    CGAL_test_assert(centerC == msC.center());
    CGAL_test_assert(centerH == msH.center());
    CGAL_test_assert(radiusC == msC.squared_radius());
    CGAL_test_assert(radiusH == msH.squared_radius());
    
    // test clear and insert methods
    msC.clear(); CGAL_test_assert(msC.is_valid(verbose));
    msH.clear(); CGAL_test_assert(msH.is_valid(verbose));
    msC.insert (PC, PC+n); CGAL_test_assert(msC.is_valid(verbose));
    msH.insert (PH, PH+n); CGAL_test_assert(msH.is_valid(verbose));
    CGAL_test_assert(centerC == msC.center());
    CGAL_test_assert(centerH == msH.center());
    CGAL_test_assert(radiusC == msC.squared_radius());
    CGAL_test_assert(radiusH == msH.squared_radius());
    
    // combined set and insert
    msC.set (PC, PC+n/2); msC.insert (PC+n/2, PC+n);
    CGAL_test_assert(msC.is_valid(verbose));
    msH.set (PH, PH+n/2); msH.insert (PH+n/2, PH+n);
    CGAL_test_assert(msH.is_valid(verbose));
    CGAL_test_assert(centerC == msC.center());
    CGAL_test_assert(centerH == msH.center());
    CGAL_test_assert(radiusC == msC.squared_radius());
    CGAL_test_assert(radiusH == msH.squared_radius());
    
    
    // test access functions
    
    // number_of_points
    CGAL_test_assert(msC.number_of_points() == n);
    CGAL_test_assert(msH.number_of_points() == n);
    
    // number_of_support_points
    CGAL_test_assert(msC.number_of_support_points() == msH.number_of_support_points());
    
    // points_begin, points_end
    int m;
    m = std::distance (msC.points_begin(), msC.points_end());
    CGAL_test_assert(m == n);
    m = std::distance (msH.points_begin(), msH.points_end());
    CGAL_test_assert(m == n);
    
    // support_points_begin, support_points_end
    m =
    std::distance (msC.support_points_begin(), msC.support_points_end());
    CGAL_test_assert(m == msC.number_of_support_points());
    m =
    std::distance (msH.support_points_begin(), msH.support_points_end());
    CGAL_test_assert(m == msH.number_of_support_points());
    
    // ambient dim
    CGAL_test_assert(msC.ambient_dimension() == D);
    CGAL_test_assert(msH.ambient_dimension() == D);
    
    // center and squared radius already tested
    
    
    // test predicates
    
    // bounded_side
    CGAL_test_assert(msC.bounded_side (centerC) == ON_BOUNDED_SIDE);
    CGAL_test_assert(msH.bounded_side (centerH) == ON_BOUNDED_SIDE);
    
    // has_on_bounded_side
    CGAL_test_assert(msC.has_on_bounded_side (centerC));
    CGAL_test_assert(msH.has_on_bounded_side (centerH));
    
    // has_on_boundary already tested in is_valid method
    // has_on_unbounded_side already tested in is_valid method
    
    // is_empty
    CGAL_test_assert(!msC.is_empty());
    CGAL_test_assert(!msH.is_empty());
    
    // is_degenerate
    CGAL_test_assert(!msC.is_degenerate());
    CGAL_test_assert(!msH.is_degenerate());
    
    
    std::ostringstream ost;           // output string
    set_ascii_mode (ost);
    ost << msC << msH << std::endl;      // write spheres
    
    std::istringstream ist (ost.str().c_str());  // input string
    set_ascii_mode (ist);
    ist >> msC >> msH;              // read spheres
    
    CGAL_test_assert(centerC == msC.center());
    CGAL_test_assert(centerH == msH.center());
    CGAL_test_assert(radiusC == msC.squared_radius());
    CGAL_test_assert(radiusH == msH.squared_radius());
    
    return 0;
}


// ===== EOF ==================================================================


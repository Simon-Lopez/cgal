#include <iostream>
#include <sstream>

#include <CGAL/basic.h>
#include <CGAL/Testsuite/assert.h>
#ifdef CGAL_USE_CORE

#include <CGAL/CORE_BigRat.h>
#include <CGAL/Needs_parens_as_product.h>
#include <CGAL/_test_algebraic_structure.h>
#include <CGAL/_test_real_embeddable.h>
#include <CGAL/_test_fraction_traits.h>
#include <CGAL/_test_rational_traits.h>

void test_io(){
    typedef CORE::BigRat NT;
    // MODE ASCII
    {
        std::stringstream ss;
        CGAL::set_ascii_mode(ss);
        ss << CGAL::oformat(NT(1));
        //std::cout << ss.str()<<std::endl;
        CGAL_test_assert( ss.str() == "1/1");
    }{
        std::stringstream ss;
        CGAL::set_ascii_mode(ss);
        ss << CGAL::oformat(NT(0));
        CGAL_test_assert( ss.str() == "0/1");
    }{
        std::stringstream ss;
        CGAL::set_ascii_mode(ss);
        ss << CGAL::oformat(NT(-1));
        CGAL_test_assert( ss.str() == "-1/1");
    }
    //MODE PRETTY
    {
        std::stringstream ss;
        CGAL::set_pretty_mode(ss);
        ss << CGAL::oformat(NT(2), CGAL::Parens_as_product_tag());
        CGAL_test_assert( ss.str() == "2");
    }{
        std::stringstream ss;
        CGAL::set_pretty_mode(ss);
        ss << CGAL::oformat(NT(1)/NT(2),CGAL::Parens_as_product_tag());
        CGAL_test_assert( ss.str() == "(1/2)");
    }{
        std::stringstream ss;
        CGAL::set_pretty_mode(ss);
        ss << CGAL::oformat(NT(-2), CGAL::Parens_as_product_tag());
        CGAL_test_assert( ss.str() == "(-2)");
    }
}

int main() {
    typedef CORE::BigRat NT;
    typedef CGAL::Field_tag Tag;
    typedef CGAL::Tag_true Is_exact;

    CGAL::test_algebraic_structure<NT,Tag, Is_exact>();
    CGAL::test_algebraic_structure<NT,Tag, Is_exact>(NT(4),NT(6),NT(15));
    CGAL::test_algebraic_structure<NT,Tag, Is_exact>(NT(-4),NT(6),NT(15));
    CGAL::test_algebraic_structure<NT,Tag, Is_exact>(NT(4),NT(-6),NT(15));
    CGAL::test_algebraic_structure<NT,Tag, Is_exact>(NT(-4),NT(-6),NT(15));
    CGAL::test_algebraic_structure<NT,Tag, Is_exact>(NT(4),NT(6),NT(-15));
    CGAL::test_algebraic_structure<NT,Tag, Is_exact>(NT(-4),NT(6), NT(15));
    CGAL::test_algebraic_structure<NT,Tag, Is_exact>(NT(4),NT(-6),NT(-15));
    CGAL::test_algebraic_structure<NT,Tag, Is_exact>(NT(-4),NT(-6),NT(-15));
  
    CGAL::test_real_embeddable<NT>();

    CGAL::test_fraction_traits<NT>(); 
    // backward compatiblity
    CGAL::test_rational_traits<NT>();  
    
    test_io();
    
  return 0;
}

#else
int main() { return 0; }
#endif // CGAL_USE_CORE

//EOF
 

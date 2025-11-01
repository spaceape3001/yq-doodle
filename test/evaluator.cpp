////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <yq/doodle/logging.hpp>
#include <yq/doodle/Project.hpp>
#include <yq/doodle/Evaluator.hpp>
#include <yq/doodle/py/Curve.hpp>
#include <yq/doodle/py/Point.hpp>
#include <yq/doodle/Project.hxx>
#include <yq/core/Any.hpp>
#include <memory>
#include <cmath>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;
using namespace yq::doodle;

Project&    project()
{
    static Project  s_project;
    
    if(s_project.is_empty()){
        Point*  a   = s_project.create<Point>();
        a->set_uid("a");
        a->attribute(SET, "foo", "bar");
        a->attribute(SET, "f", "1");
        a->attribute(SET, "b", "f");
        a->attribute(SET, "c", "f+b");
        a->attribute(SET, "d", "t");
        a->attribute(SET, "r", "1");
        a->attribute(SET, "az", "t");
        
        Point* b    = s_project.create<Point>();
        b->set_uid("b");
        b->attribute(SET, "x", "a.x+3");
        b->attribute(SET, "y", "a.y+6");
    }
    
    return s_project;
}

bool    sdouble(const Any& valx, double val, double ep=1e-14)
{
    auto dd = to_double(valx);
    if(!dd){
        std::cerr << "Extraction of value failed: " << dd.error().message() << "\n";
        return false;
    }
    
    if(::fabs(*dd - val) <= ep)
        return true;
    return false;
}

int main(){
    log_to_std_output();
    Meta::init();

    "project"_test = []{
        Project& prj    = project();
        expect(prj.count(OBJECT) == 2);
        expect(prj.count(OBJECT, UID, "a") == 1);
        expect(prj.count(OBJECT, UID, "A") == 1);
        expect(prj.count(OBJECT, UID, "b") == 1);
        expect(prj.count(OBJECT, UID, "B") == 1);
        expect(prj.count(OBJECT, UID, "c") == 0);
        expect(prj.count(OBJECT, UID, "C") == 0);
    };
    
    "attribute"_test = []{
        Project& prj    = project();
        
        const Point*p   = prj.object<Point>(UID, "a");
        expect(p != nullptr);
        if(!p)
            return ;
        expect(p->attribute("foo") == "bar");
    };
    
    "evaluate1"_test = []{
        Evaluator       eval(project());
        any_x   val = eval.evaluate(UID, "a", "f");
        expect((bool) val == true);
        if(!val)
            return ;
        expect(sdouble(*val, 1.0) == true);
    };
    
    "evaluate2"_test = []{
        Evaluator       eval(project());
        any_x   val = eval.evaluate(UID, "a", "b");
        expect((bool) val == true);
        if(!val)
            return ;
        expect(sdouble(*val, 1.0) == true);
    };

    "evaluate3"_test = []{
        Evaluator       eval(project());
        any_x   val = eval.evaluate(UID, "a", "c");
        expect((bool) val == true);
        if(!val)
            return ;
        expect(sdouble(*val, 2.0) == true);
    };

    "evaluate4"_test = []{
        Evaluator       eval(project());
        eval.set_override("t", Any(2.));
        expect(eval.is_override("t") == true);
        any_x   val = eval.evaluate(UID, "a", "d");
        if(!val)
            return ;
        expect(sdouble(*val, 2.0) == true);
    };
    
    "evaluate5"_test = []{
        Evaluator       eval(project());
        
        eval.set_override("t", Any(90.));
        expect(sdouble(eval.get_override("t"), 90.0) == true);
        
        Project&    p   = project();
        const DObject* obj  = p.object(UID, "a");
        expect(obj != nullptr);
        
        any_x   x = eval.evaluate(UID, "a", "x");
        any_x   y = eval.evaluate(UID, "a", "y");
        expect((bool) x == true);
        expect((bool) y == true);
        if(!x)
            return ;
        if(!y)
            return ;
        
        expect(sdouble(*x, 1.0) == true);
        expect(sdouble(*y, 0.0) == true);
    };
    
    "evaluate6"_test = []{
        Evaluator       eval(project());
        
        eval.set_override("t", Any(90.));
        any_x   x = eval.evaluate(UID, "b", "x");
        any_x   y = eval.evaluate(UID, "b", "y");
        expect((bool) x == true);
        expect((bool) y == true);
        if(!x)
            return ;
        if(!y)
            return ;
        
        expect(sdouble(*x, 4.0) == true);
        expect(sdouble(*y, 6.0) == true);
    };
    
    return ut::cfg<>.run();
};

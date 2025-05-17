////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <doodle/logging.hpp>
#include <doodle/Project.hpp>
#include <doodle/py/Point.hpp>
#include <doodle/Project.hxx>
#include <memory>

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
    }
    
    return s_project;
}


int main(){
    log_to_std_output();
    
    "project"_test = []{
        Project& prj    = project();
        expect(prj.count(OBJECT) == 1);
        expect(prj.count(OBJECT, UID, "a") == 1);
        expect(prj.count(OBJECT, UID, "A") == 1);
        expect(prj.count(OBJECT, UID, "b") == 0);
        expect(prj.count(OBJECT, UID, "B") == 0);
    };
    
    
    return ut::cfg<>.run();
};

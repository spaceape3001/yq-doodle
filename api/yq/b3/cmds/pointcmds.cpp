////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/b3/Doc.hpp>
#include <yq/b3/Parser.hpp>
#include <yq/b3/spatial/Point.hpp>
#include <yq/b3/spatial/PointLine.hpp>
#include <yq/math/trigonometry.hpp>

#include <format>
#include <iostream>
#include <yq/b3/Frame.hxx>
#include <yq/shape/AxBox2.hxx>
#include <yq/vector/Vector3.hxx>

using namespace yq;
using namespace yq::b3;


// command "vv" will be an expression based line... TBD?

////////////////////////////////////////////////////////////////////////////////


static bool cmdPointMode(Parser& p, const ArgList& pArgs, const ArgMap&)
{
    Frame*  f   = p.frame();
    if(!f){
        p.gripe("No current frame");
        return false;
    }

    PointType       pt  = decode_point_type(pArgs.value(0));
    if(pt == PointType::Unknown)
        pt      = PointType::D3;

    p.set_frame_point_type(f, pt);
    return true;
}

YQ_B3_COMMAND("pm", ifArgExact, 1, cmdPointMode);

////////////////////////////////////////////////////////////////////////////////


static bool cmdPrintPoint(Parser& p, const ArgList&, const ArgMap&)
{
    Point*  pt  = dynamic_cast<Point*>(p.last());
    if(pt){
        std::cout << "{Point Request: " << p.file() << "@" << p.line() << "}: " 
            << pt->define().x << ", " << pt->define().y << ", " << key_for(pt->type())
            << " " << pt->define().z << "\n";
    }
    return true;
}

YQ_B3_COMMAND("pp", ifNone, 0, cmdPrintPoint);


////////////////////////////////////////////////////////////////////////////////

static auto    pointsFor(Frame* f)
{
    Map<std::string, Point*, IgCase>    ret;
    if(!f)
        return ret;
    
    int     n   = 1;
    f->children([&](Obj* obj){
        ++n;
        Point*p = dynamic_cast<Point*>(obj);
        if(!p)
            return ;
        std::string k(p->name());
        if(k.empty())
            k   = std::format("(unk) {}", n);
        ret[k]  = p;
    });
    return ret;
}

static bool cmdPointTable(Parser& p, const ArgList&, const ArgMap&)
{
    //  TODO 
    //bool  all  = (nArgs.get("full", "no").lower() == "yes");
    
    auto pts    = pointsFor(p.frame());
    size_t  mx   = 0;
    for(auto& itr : pts)
        mx  = std::max(mx, itr.first.size());
    
    for(auto& itr : pts){
        std::cout.width(mx);
        std::cout.setf(std::ios::left);
        std::cout << itr.first;
        std::cout.width(1);
        std::cout << " := ";
        std::cout << itr.second->define().x << ", ";
        std::cout << itr.second->define().y << ", ";
        std::cout << key_for(itr.second->type()) << ", ";
        std::cout << itr.second->define().z << "\n";
    }

    return true;
}
YQ_B3_COMMAND("pt", ifNone, 0, cmdPointTable);

////////////////////////////////////////////////////////////////////////////////


static bool cmdPoint(Parser& p, const ArgList&pArgs, const ArgMap&sArgs) 
{
    Frame*f     = p.frame();
    Point*  pt      = new Point({.args=pArgs, .attrs=sArgs, .frame=f});
    if(PointLine*   ap  = dynamic_cast<PointLine*>(f))
        ap -> point(ADD, pt);
    p << pt;
    return true;
}

YQ_B3_COMMAND("v", ifNone, 0, cmdPoint);

////////////////////////////////////////////////////////////////////////////////


static bool cmdArcPoints(Parser&p, const ArgList&pArgs, const ArgMap&sArgs) 
{
    Frame* f    = p.frame();
    if(!f){
        p.gripe("No frame!");
        return false;
    }
    
    Vector3D     st   = { 0., 0., 0. };
    double       r    = 0.;
    unit::Degree th0  = 0.;
    unit::Degree th1  = 360.;
    int          cnt  = 0, n0=0;
    PointLine*   ap   = dynamic_cast<PointLine*>(f);
    
    st.z   = sArgs.real("z", 0.);
    cnt     = sArgs.integer("n", 0);
    if(cnt && (cnt <= 1)){
        p.gripe("Count has to be at least two");
        return false;
    }

    Point*  ps  = ap ? ap->point(LAST) : nullptr;
    if(sArgs.has("use"))
        ps      = dynamic_cast<Point*>(f->find(sArgs.string("use")));

    if(pArgs.size() < 5){
        if(!ps){
            p.gripe("Need a starting point!");
            return false;
        }
        st      = ps->define();
        ++n0;
    }
    
    switch(pArgs.size()){
    case 2:
        if(!ap){
            p.gripe("Insufficient arguments w/o a good point acceptor");
            return false;
        }
        
        if(!ap->heading(VALID)){
            p.gripe("Need to specify start heading if insufficient points defined");
            return false;
        }
        
        r       = fabs(pArgs.length(0));
        th0     = ap->heading(END);
        th1     = pArgs.angle(1);
        break;
        
    case 4:
        st.z       = pArgs.length(3);
        //  fall thru
    case 3:
        r       = fabs(pArgs.length(0));
        th0     = pArgs.angle(1);
        th1     = pArgs.angle(2);
        break;
    case 6:
        st.z    = pArgs.length(5);
        //  fall thru
    case 5:
        st.x    = pArgs.length(0);
        st.y    = pArgs.length(1);
        r       = fabs(pArgs.length(2));
        th0     = pArgs.angle(3);
        th1     = pArgs.angle(4);
        break;
    default:
        p.gripe("Too many arguments!");
        return false;
    
    }
    
    if(!cnt)
        cnt   = 1 + (int) (fabs((th1-th0).value)/5.); // default
    
    //  convert to radians;
    
    std::string    id  = sArgs.string("id");
    double  ox, oy;
    
    Vector<Vector2D>  coords;
    
    if(th1 < th0){  // backwards
        ox  = st.x - r * cos(th0);
        oy  = st.y + r * sin(th0);

        for(int n=n0;n<=cnt;++n){
            unit::Radian  th  = th0 + unit::Radian(th1-th0) * ((double) n) / (double) cnt;
            double  x   = ox + r * cos(th);
            double  y   = oy - r * sin(th);
            coords << Vector2D(x,y);
        }
    } else {
        ox  = st.x + r * cos(th0);
        oy  = st.y - r * sin(th0);

        for(int n=n0;n<=cnt;++n){
            unit::Radian  th  = th0 + unit::Radian(th1-th0) * ((double) n) / (double) cnt;
            double  x   = ox - r * cos(th);
            double  y   = oy + r * sin(th);
            coords << Vector2D(x,y);
        }
    }
    
    //  Now, we need to push this along......
    int  nid   = 1;
    for(Vector2D c : coords){
        ArgMap cnArgs;
        if(!id.empty()){
            cnArgs.attrs["id"] = std::format("{}{}", id, nid);
            ++nid;
        }
        
        Point*  p2 = nullptr;
        if(st.z != 0.){
            Vector3D   cc = { c.x, c.y, st.z };
            p2  = new Point(cc, {.attrs=cnArgs, .frame=f});
        } else
            p2  = new Point(c,  {.attrs=cnArgs, .frame=f});
        if(ap)
            ap->point(ADD, p2);
        p << p2;
    }

    return true;
}

YQ_B3_COMMAND("va", ifNone, 2, cmdArcPoints);

////////////////////////////////////////////////////////////////////////////////

namespace yq::b3 {
    bool    addBoxPoints(Parser&p, Frame* parent, const ArgList& pArgs, const ArgMap&sArgs, const std::string& id)
    {
        PointLine*   ap     = dynamic_cast<PointLine*>(parent);

        double          x   = 0;
        double          y   = 0;
        double          z   = 0.;
        double          w   = 0;
        double          h   = 0;

        if((pArgs.size() < 4) && (pArgs.size() != 2)){
            p.gripe("Expecting two or four arguments!");
        }

        switch(pArgs.size()){
        case 2:
            w       = pArgs.length(0);
            h       = pArgs.length(1);

            if(sArgs.has("use")){
                Point*  ps  = dynamic_cast<Point*>(parent->find(sArgs.string("use")));
                if(!ps){
                    p.gripe("Cannot find the use point");
                    return false;
                }
                
                x       = ps->define().x;
                y       = ps->define().y;
                z       = ps->define().z;
            } else if(ap) {
                Point* ps   = ap->point(LAST);
                if(ps){
                    x       = ps->define().x;
                    y       = ps->define().y;
                    z       = ps->define().z;
                }
            }
            
            break;
        case 4:
            x       = pArgs.length(0);
            y       = pArgs.length(1);
            w       = pArgs.length(2);
            h       = pArgs.length(3);
            break;
        case 5:
            x       = pArgs.length(0);
            y       = pArgs.length(1);
            z       = pArgs.length(2);
            w       = pArgs.length(3);
            h       = pArgs.length(4);
            break;
        default:
            p.gripe("Expecting 2, 4, or 5 arguments!");
            return false;;
        }
        
        if(sArgs.has("z0"))
            z   = sArgs.length("z0", z);
        else if(sArgs.has("z"))
            z   = sArgs.length("z", z);
        
        AxBox2D     box({x,y},{x+w,y+h});
        
        Point*      pnw = nullptr;
        Point*      pne = nullptr; 
        Point*      pse = nullptr;
        Point*      psw = nullptr;
        
        pnw = new Point(box.lh().z(z), { .frame=parent, .name=id+"@nw" });
        pne = new Point(box.hh().z(z), { .frame=parent, .name=id+"@ne" });
        pse = new Point(box.hl().z(z), { .frame=parent, .name=id+"@se" });
        psw = new Point(box.ll().z(z), { .frame=parent, .name=id+"@sw" });
        
        if(ap){
            ap->point(ADD, pnw);
            ap->point(ADD, pne);
            ap->point(ADD, pse);
            ap->point(ADD, psw);
        }
        p << psw;
        return true;
    }
}

static bool cmdAddBoxPoints(Parser& p, const ArgList& pArgs, const ArgMap& sArgs)
{
    return addBoxPoints(p, p.frame(), pArgs, sArgs, sArgs.string("id"));
}

YQ_B3_COMMAND("vbox", ifNone, 0, cmdAddBoxPoints);


////////////////////////////////////////////////////////////////////////////////

static bool cmdProjectPoint(Parser& p, const ArgList& pArgs, const ArgMap& sArgs)
{
    Frame*f             = p.frame();
    PointLine*   ap  = dynamic_cast<PointLine*>(f);
    
    Vector3D       st;
    double          r   = 0.;
    unit::Degree    th  = 0.;

    st.z   = sArgs.length("z", 0.);
    
    Point*      ps  = ap ? ap->point(LAST) : nullptr;
    if(sArgs.has("use")){
        ps      = dynamic_cast<Point*>(f->find(sArgs.string("use")));
    }
    
    switch(pArgs.size()){
    case 1:
        if(!ap){
            p.gripe("Frame must be capable of being point-aware!");
            return false;
        }
        if(!ap->heading(VALID)){
            p.gripe("Need points (or add a heading)");
            return false;
        }
        if(!ps){
            p.gripe("Need a starting point (or specify it!)");
            return false;
        }
        st      = ps->define();
        th      = ap->heading(END);
        r       = pArgs.length(0);
        break;
    case 3:
        st.z    = pArgs.length(2);
    case 2:
        if(!ap){
            p.gripe("Frame must be capable of being point-aware!");
            return false;
        }
        if(!ps){
            p.gripe("Need a starting point (or specify it!)");
            return false;
        }
        st      = ps->define();
        th      = pArgs.angle(1);
        r       = pArgs.length(0);
        break;
        return false;
    case 5:
        st.z     = pArgs.length(4);
    case 4:
        st.x    = pArgs.length(0);
        st.y    = pArgs.length(1);
        r       = pArgs.length(2);
        th      = pArgs.angle(3);
        break;
    default:
        p.gripe("Too many arguments!");
        return false;
    }
    
    if(!ps){
        ps      = (st.z != 0.) ? new Point(st, {.frame=f}) : new Point(st.xy(), {.frame=f});
        if(ap)
            ap->point(ADD,ps);
        p << ps;
    }
    
    st.x    += r * sin(th);
    st.y    += r * cos(th);
    
    Point*      pn  = (st.z != 0.) ? new Point(st, {.attrs=sArgs, .frame=f}) : new Point(st.xy(), {.attrs=sArgs, .frame=f});
    if(ap)
        ap -> point(ADD,pn);
    p << pn;
    return true;
}

YQ_B3_COMMAND("vp", ifNone, 1, cmdProjectPoint);


////////////////////////////////////////////////////////////////////////////////

static bool cmdExistingPoint(Parser& p, const ArgList&pArgs, const ArgMap&sArgs) 
{
    Frame*f = p.frame();
    PointLine*   ap  = dynamic_cast<PointLine*>(f);
    if(pArgs.empty()){
        p.gripe("Need an ID!");
        return false;
    }
    if(!ap){
        p.gripe("Needs to be in a point-line frame!");
        return false;
    }
    
    Point* pt      = f->point(pArgs.string(0));
    if(!pt){
        p.gripe("Cannot find specified point!");
        return false;
    }
    
    ap -> point(ADD, pt);
    return true;
}


YQ_B3_COMMAND("vx", ifNone, 0, cmdExistingPoint);

////////////////////////////////////////////////////////////////////////////////

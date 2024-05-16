
#include <iostream>
#include "SVGElements.hpp"
#include "external/tinyxml2/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

namespace svg
{
    void readSVG(const string& svg_file, Point& dimensions, vector<SVGElement *>& svg_elements)
    {
        XMLDocument doc;
        XMLError r = doc.LoadFile(svg_file.c_str());
        if (r != XML_SUCCESS)
        {
            throw runtime_error("Unable to load " + svg_file);
        }
        XMLElement *xml_elem = doc.RootElement();

        dimensions.x = xml_elem->IntAttribute("width");
        dimensions.y = xml_elem->IntAttribute("height");
        
        SVGElement elem;

        for (XMLElement *child = elem->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
    {
        readElements(child, svg_elements);
    }
        

    }


    void readElements(XMLElement* elem, vector<SVGElement *>& svg_elements){
        vector<Point> points;
        if(strcmp(elem->Name(), "circle") == 0){
            SVGElement *circle = new Ellipse(Color(parse_color(elem->Attribute("fill"))),Point(elem->IntAtributte("cx"), elem->IntAtributte("cy")), Point(elem->IntAttribute("r"), elem->IntAttribute("r")));
            svg_elements.push_back(circle);
            ~circle;
        }

        else if(strcmp(elem->Name(), "ellipse") == 0){
            SVGElement *ellipse = new Ellipse(Color(parse_color(elem->Attribute("fill"))),Point(elem->IntAtributte("cx"), elem->IntAtributte("cy")), Point(elem->IntAttribute("rx"), elem->IntAttribute("ry")));
            svg_elements.push_back(ellipse);
            ~ellipse;
        }

        else if(strcmp(elem->Name(), "line") == 0){
            points.pushback(Point(elem->IntAttribute("x1"),elem->IntAttribute("y1")));
            points.pushback(Point(elem->IntAttribute("x2"),elem->IntAttribute("y2")));
            SVGElement *line = new PolyLine(Color(parse_color(elem->Attribute("stroke"))), points);
            svg_elements.push_back(line);
            points.clear();
            ~line;
        }

        else if(strcmp(elem->Name(), "polyline") == 0){
            istringstream iss(elem->IntAttribute(points));
            int x, y;
            for(string l; iss >> l)
            {
                x = l.substr(0,l.find_first_of(",") - 1);
                y = l.substr(l.find_first_of(",") + 1);
                points.pushback(Point(x,y));
            }
            SVGElement *polyline = new PolyLine(Color(parse_color(elem->Attribute("stroke"))), points);
            svg_elements.push_back(polyline);
            points.clear();
            ~polyline;
        }

        else if(strcmp(elem->Name(), "polygon") == 0){
            istringstream iss(elem->IntAttribute(points));
            int x, y;
            for(string l; iss >> l)
            {
                x = l.substr(0,l.find_first_of(",") - 1);
                y = l.substr(l.find_first_of(",") + 1);
                points.pushback(Point(x,y));
            }
            SVGElement *polygon = new Polygon(Color(parse_color(elem->Attribute("fill"))), points);
            svg_elements.push_back(polygon);
            points.clear();
            ~polygon;
        }
        else if(strcmp(elem->Name(), "rect") == 0){
            
            Point tl(elem->IntAttribute("x"), elem->IntAttribute("y"));
            Point bl(tl.x , tl.y + elem->IntAttribute("height")), tr(tl.x + elem->IntAttribute("width"), tl.y), br(tl.x + elem->IntAttribute("width"), tl.y + elem->IntAttribute("height"));
        
            points.pushback(tl);
            points.pushback(bl);
            points.pushback(tr);
            points.pushback(br);
        
            SVGElement *polygon = new Polygon(Color(parse_color(elem->Attribute("fill"))), points);
            svg_elements.push_back(polygon);
            points.clear();
            ~polygon;
        }

        else if(strcmp(elem->Name(), "g") == 0){
            for (XMLElement *child = elem->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
            {
                readElements(child, svg_elements);
            }
            
        }

    }
}
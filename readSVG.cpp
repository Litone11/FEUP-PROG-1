
#include <iostream>
#include <sstream>
#include "SVGElements.hpp"
#include "external/tinyxml2/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

namespace svg
{
    void readElements(XMLElement* elem, vector<SVGElement *>& svg_elements){
        vector<Point> points;
        if(strcmp(elem->Name(), "circle") == 0){
            SVGElement *circle = new Ellipse(Color(parse_color(elem->Attribute("fill"))),{elem->IntAttribute("cx"), elem->IntAttribute("cy")}, {elem->IntAttribute("r"), elem->IntAttribute("r")});
            svg_elements.push_back(circle);
        }

        else if(strcmp(elem->Name(), "ellipse") == 0){
            SVGElement *ellipse = new Ellipse(Color(parse_color(elem->Attribute("fill"))),{elem->IntAttribute("cx"), elem->IntAttribute("cy")}, {elem->IntAttribute("rx"), elem->IntAttribute("ry")});
            svg_elements.push_back(ellipse);
        }

        else if(strcmp(elem->Name(), "line") == 0){
            points.push_back({(elem->IntAttribute("x1"),elem->IntAttribute("y1"))});
            points.push_back({elem->IntAttribute("x2"),elem->IntAttribute("y2")});
            SVGElement *line = new PolyLine(Color(parse_color(elem->Attribute("stroke"))), points);
            svg_elements.push_back(line);
            points.clear();
        }

        else if(strcmp(elem->Name(), "polyline") == 0){
            istringstream iss(elem->Attribute("points"));
            for(string l; iss >> l;)
            {
                int x = stoi(l.substr(0,l.find_first_of(",") - 1));
                int y = stoi(l.substr(l.find_first_of(",") + 1));
                points.push_back({x,y});
            }
            SVGElement *polyline = new PolyLine(Color(parse_color(elem->Attribute("stroke"))), points);
            svg_elements.push_back(polyline);
            points.clear();
        }

        else if(strcmp(elem->Name(), "polygon") == 0){
            istringstream iss(elem->Attribute("points"));
            for(string l; iss >> l;)
            {
                int x = stoi(l.substr(0,l.find_first_of(",") - 1));
                int y = stoi(l.substr(l.find_first_of(",") + 1));
                points.push_back({x,y});
            }
            SVGElement *polygon = new Polygon(Color(parse_color(elem->Attribute("fill"))), points);
            svg_elements.push_back(polygon);
            points.clear();
        }
        else if(strcmp(elem->Name(), "rect") == 0){
            
            struct Point tl{elem->IntAttribute("x"), elem->IntAttribute("y")};
            struct Point bl{tl.x , tl.y + elem->IntAttribute("height")}, tr{tl.x + elem->IntAttribute("width"), tl.y}, br{tl.x + elem->IntAttribute("width"), tl.y + elem->IntAttribute("height")};
        
            points.push_back(tl);
            points.push_back(bl);
            points.push_back(tr);
            points.push_back(br);
        
            SVGElement *polygon = new Polygon(Color(parse_color(elem->Attribute("fill"))), points);
            svg_elements.push_back(polygon);
            points.clear();
        }

        else if(strcmp(elem->Name(), "g") == 0){
            for (XMLElement *child = elem->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
            {
                readElements(child, svg_elements);
            }
            
        }
        else if(strcmp(elem->Name(), "use") == 0){
            string href = elem->Attribute("href");
            href = href.substr(1); // remove the '#' character
            SVGElement *original = nullptr;
            for(SVGElement *e : svg_elements){
                if(e->id == href){
                original = e;
                break;
                }
            }
            if(original!= nullptr){
            // create a new element with the same properties as the original
            SVGElement *copy = original->clone();
            // apply any transformations defined in the 'transform' attribute
            string transform = elem->Attribute("transform");
            if(!transform.empty()){
            // parse the transform attribute and apply the transformations to the copy
            //...
            }
            svg_elements.push_back(copy);
            }
        }

    }

    void readSVG(const string& svg_file, Point& dimensions, vector<SVGElement *>& svg_elements)
    {
        svg_elements.clear();
        XMLDocument doc;
        XMLError r = doc.LoadFile(svg_file.c_str());
        if (r != XML_SUCCESS)
        {
            throw runtime_error("Unable to load " + svg_file);
        }
        XMLElement *xml_elem = doc.RootElement();

        dimensions.x = xml_elem->IntAttribute("width");
        dimensions.y = xml_elem->IntAttribute("height");
    
        for (XMLElement *child = xml_elem->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
    {
        readElements(child, svg_elements);
    }
        

    }

    
}
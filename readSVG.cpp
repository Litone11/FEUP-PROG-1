
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <limits>
#include <cstring>
#include <algorithm>
#include "SVGElements.hpp"
#include "external/tinyxml2/tinyxml2.h"
#include "Point.hpp"
#include "Color.hpp"

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

        // Get the root element of the SVG document
        XMLElement *root = doc.RootElement();
        dimensions.x = root->IntAttribute("width");
        dimensions.y = root->IntAttribute("height");

        // Iterate over child elements of the root
        for (XMLElement* child = root->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
        {
            const char* elementName = child->Name();

            // Check if the element is a circle
            if (strcmp(elementName, "circle") == 0)
            {
                int cx = child->IntAttribute("cx");
                int cy = child->IntAttribute("cy");
                int r = child->IntAttribute("r");
                Color fillColor = parse_color(child->Attribute("fill"));
                SVGElement *circle = new Circle(cx, cy, r, fillColor);

                svg_elements.push_back(circle);
            }
            // Check if the element is an ellipse
            else if (strcmp(elementName, "ellipse") == 0)
            {
                int cx = child->IntAttribute("cx");
                int cy = child->IntAttribute("cy");
                int rx = child->IntAttribute("rx");
                int ry = child->IntAttribute("ry");
                Color fillColor = parse_color(child->Attribute("fill"));
                SVGElement *ellipse = new Ellipse(fillColor, Point(cx, cy), Point(rx, ry));
                svg_elements.push_back(ellipse);
            }
            // Check if the element is a line
            else if (strcmp(elementName, "line") == 0)
            {
                int x1 = child->IntAttribute("x1");
                int y1 = child->IntAttribute("y1");
                int x2 = child->IntAttribute("x2");
                int y2 = child->IntAttribute("y2");
                Color strokeColor = parse_color(child->Attribute("stroke"));
                SVGElement *line = new Line(Point(x1, y1), Point(x2, y2), strokeColor);
                svg_elements.push_back(line);
            } else if (strcmp(elementName, "polyline") == 0) {
                const char* pointsStr = child->Attribute("points");
                istringstream pointsStream(pointsStr);
                vector<Point> points;
                string pointPair;

                while (getline(pointsStream, pointPair, ' ')) {
                    replace(pointPair.begin(), pointPair.end(), ',', ' ');
                    istringstream pointStream(pointPair);
                    int x, y;
                    pointStream >> x >> y;
                    points.emplace_back(x, y);
                }

                Color strokeColor = parse_color(child->Attribute("stroke"));
                SVGElement *polyline = new Polyline(points, strokeColor);
                svg_elements.push_back(polyline);

            } else if (strcmp(elementName, "rect") == 0) {
                int x = child->IntAttribute("x");
                int y = child->IntAttribute("y");
                int width = child->IntAttribute("width");
                int height = child->IntAttribute("height");
                Color fillColor = parse_color(child->Attribute("fill"));
                SVGElement *rectangle = new Rectangle(Point(x, y), Point(x + width, y + height), fillColor);
                svg_elements.push_back(rectangle);
            }
            // Check if the element is a polyline
            else if (strcmp(elementName, "polygon") == 0) {
                const char* pointsStr = child->Attribute("points");
                istringstream pointsStream(pointsStr);
                vector<Point> points;
                string pointPair;

                while (getline(pointsStream, pointPair, ' ')) {
                    replace(pointPair.begin(), pointPair.end(), ',', ' ');
                    istringstream pointStream(pointPair);
                    int x, y;
                    pointStream >> x >> y;
                    points.emplace_back(x, y);
                }

                Color fillColor = parse_color(child->Attribute("fill"));
                SVGElement *polygon = new Polygon(points, fillColor);
                svg_elements.push_back(polygon);

            //parse_transform(s, xml_element)
            //svg_elements.push_back()
        }
    }
}
}
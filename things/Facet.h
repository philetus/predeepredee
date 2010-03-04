/*  Facet.h
 *
 *  triangle in a graphics mesh
 *  - defined by a surface normal and 3 vectors
 *  
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */

#ifndef PDPD_GEOMETRY_FACET
#define PDPD_GEOMETRY_FACET

#include "../geometry/Vector3.h"
#include "../util/Iterator.h"

namespace pdpd
{
    namespace things
    {
        class Facet
        {
            Vector3 normal;
            Vector3 vertex0;
            Vector3 vertex1;
            Vector3 vertex2;
            
            static const int vertex_count = 3; // facets are triangles
            
            // *** iterator over vertices
            class VertexIterator;
            friend VertexIterator;
            class VertexIterator : public util::Iterator<Facet>
            {
                int index;
                Facet& facet;
            public:
                VertexIterator(Facet& f) : facet(f), index(0) {}
                virtual bool has_next() { return index < facet.vertex_count; }
                virtual Vertex3 next() { return facet.get_vertex(index++); }
            } // FacetIterator

        public:
            
            // construct from a normal and three vertices
            Facet(
                geometry::Vector3 n, 
                geometry::Vector3 v0, 
                geometry::Vector3 v1, 
                geometry::Vector3 v2)
            :
            normal(n), vertex0(v0), vertex1(v1), vertex2(v2) 
            {}
            
            // copy-constructor copies normal and vertex vectors from prototype
            Facet(const Facet& prototype)
            :
            normal(prototype.normal), 
            vertex0(prototype.vertex0), 
            vertex1(prototype.vertex1),
            vertex2(prototype.vertex2)
            {}
            
            util::Iterator<geometry::Vector3>* iter_vertices()
                { return new VertexIterator(*this); }
            
            // TODO: use an array for vertices?
            // return vertex by index
            Vertex3 get_vertex(int index)
            {
                switch(index)
                {
                case 0: return vertex0;
                case 1: return vertex1;
                case 2: return vertex2;
                }
            }
            
            void get_gl_normal(float* m3)
            {
                for(int i = 0; i < 3; i++) m3[i] = normal[i];
            }
            
            void get_gl_vertex(float* m3, int index)
            {
                Vertex3 vertex = get_vertex(index);
                for(int i = 0; i < 3; i++) m3[i] = vertex[i];
            }
        }
    }
}
#endif // PDPD_GEOMETRY_FACET

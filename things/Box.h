/*  Box.h
 *
 *  simple atomic thing
 *
 *  defined by a size (width, depth, height) and a position transform
 *
 *  default color is gray
 *  
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */
 
#ifndef PDPD_THINGS_BOX
#define PDPD_THINGS_BOX

#include <deque>
#include "../geometry/Transform3.h"
#include "../geometry/Vector3.h"
#include "../util/DequeIterator.h"
#include "AtomicThing.h"
#include "Vertex.h"
#include "Facet.h"

namespace pdpd
{
    namespace things
    {
        /*
         *  atomic things' interface requires a material and iterators
         *  over its vertices and facets to facilitate rendering and simulation
         */
        class Box : public AtomicThing
        {
            // Material* material; // defines what box is made of
            Transform3 origin; // position & orientation of box
            Scale3 scale; // scale vector representing size of box
            double mass; // mass of box (in grams?)
            
            static const float normal_table[][]; // table of normals by facet
            static const int vertex_table[][]; // table of vertices by facet
            
            // *** iterator over facets
            class FacetIterator;
            friend FacetIterator;
            class FacetIterator : public util::Iterator<Facet>
            {
                static const int facet_count = 12;
                int index;
                Box& box;
            public:
                FacetIterator(Box& a_box) box(a_box), index(0) {}
                virtual bool has_next() { return index < facet_count; }
                virtual Facet next();
            } // FacetIterator
            
        public:
            Box(geometry::Scale3 a_scale, double a_mass = 0.0);
            ~Box() { delete material; delete position; delete half_size; }
            
            // *** thing interface
            virtual geometry::Aabb3 get_aabb();
            virtual geometry::Transformation3 get_offset();
            virtual bool is_dynamic();
            virtual bool is_child();
            
            // *** atomic thing interface
            // virtual materials::Material* get_material() { return material }
            virtual util::Iterator<Vertex>* iter_vertices();
            virtual util::Iterator<Facet>* iter_facets()
                { return new FacetIterator(*this); }
            virtual double get_mass() { return mass; }
            virtual void set_transformation(
                const geometry::Transformation3 new_transformation)
            { transformation.crib(new_transformation); }
            
            // component geometry created on the fly from scale & transformation
            Vertex get_vertex(int index);
            Facet get_facet(int index);
            
        }
        const float Box::normal_table[][] = 
            {{-1.0, 0.0, 0.0},
             {-1.0, 0.0, 0.0},
             {0.0, -1.0, 0.0},
             {0.0, -1.0, 0.0},
             {0.0, 0.0, -1.0},
             {0.0, 0.0, -1.0},
             {1.0, 0.0, 0.0},
             {1.0, 0.0, 0.0},
             {0.0, 1.0, 0.0},
             {0.0, 1.0, 0.0},
             {0.0, 0.0, 1.0},
             {0.0, 0.0, 1.0}};

        const int Box::vertex_table[][] = 
            {{0, 1, 3},  // -x
             {0, 3, 2},  // -x
             {0, 4, 5},  // -y
             {0, 5, 1},  // -y
             {0, 2, 6},  // -z
             {0, 6, 4},  // -z
             {7, 5, 4},  // +x
             {7, 4, 6},  // +x
             {7, 6, 2},  // +y
             {7, 2, 3},  // +y
             {7, 3, 1},  // +z
             {7, 1, 5}}; // +z
    }
}
#endif // PDPD_THINGS_ATOMIC_THING

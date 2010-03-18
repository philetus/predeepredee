/*  Flexure.h
 *
 *  a soft body cloth
 *  
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */
 
#ifndef PDPD_THINGS_FLEXURE
#define PDPD_THINGS_FLEXURE

#include <iostream>

#include "SoftThing.h"
#include "../util/Iterator.h"
#include "../geometry/Vector3.h"
#include "../geometry/Transformation3.h"
#include "../geometry/Facet.h"

namespace pdpd
{
    namespace things
    {
        class Flexure : public SoftThing
        {
        protected:            
            geometry::Vector3 vertices[2][2];
            int resolution[2];
            int fixed_corners;
            
            // *** iterator over facets
            friend class FacetIterator;
            class FacetIterator : public util::Iterator<geometry::Facet>
            {
                int facet_count;
                int index;
                Flexure& flexure;
            public:
                FacetIterator(Flexure& flxr) 
                :
                facet_count(flxr.soft_body->m_faces.size() * 2),
                index(0),
                flexure(flxr)
                {}
                virtual bool has_next() { return index < facet_count; }
                virtual geometry::Facet next()
                    { return flexure.get_facet(index++); }
            }; // FacetIterator

            
        public:
            Flexure(
                const geometry::Vector3& v00,
                const geometry::Vector3& v10,
                const geometry::Vector3& v01,
                const geometry::Vector3& v11,
                float* clr,
                float mss = 0.0,
                int x_rs = 9,
                int y_rs = 9,
                int fxd_crnrs = 4 + 8, // v01 (v10?) & v11
                bool chld = false)
            :
            SoftThing(clr, mss, chld),
            fixed_corners(fxd_crnrs)
            {
                vertices[0][0] = v00;
                vertices[1][0] = v10;
                vertices[0][1] = v01;
                vertices[1][1] = v11;
                
                resolution[0] = x_rs;
                resolution[1] = y_rs;
            }
            
            btSoftBody* init_soft_body(btSoftBodyWorldInfo& sftbdy_wrld_inf)
            {
                std::cout << "initializing soft body" << std::endl;
                
                soft_body = btSoftBodyHelpers::CreatePatch(
                    sftbdy_wrld_inf,
                    vertices[0][0],
                    vertices[1][0],
                    vertices[0][1],
                    vertices[1][1],
                    resolution[0],
                    resolution[1],
                    fixed_corners,
                    true);
                
                //std::cout << "fixed corners: " << fixed_corners << std::endl;

                //std::cout << "received soft body pointer: " << soft_body << std::endl;
                
                //std::cout << "setting mass" << std::endl;
                
                soft_body->setTotalMass(mass);
                
                //std::cout << "done initializing soft body" << std::endl;

                return soft_body;
            }
            
            // *** thing interface
            void get_parent_frame(geometry::Transformation3*) {}
            void get_gl_parent_frame(btScalar*) {}

            // *** atomic thing interface
            util::Iterator<geometry::Vector3>* iter_vertices()
                { return NULL; }
            util::Iterator<geometry::Facet>* iter_facets()
                { return new FacetIterator(*this); }
            
            geometry::Facet get_facet(int index)
            {
                int i = index / 2;
                bool side = static_cast<bool>(index % 2);
                
                if(side)
                {
                    return geometry::Facet(
                        geometry::Vector3(soft_body->m_faces[i].m_normal),
                        geometry::Vector3(soft_body->m_faces[i].m_n[0]->m_x),
                        geometry::Vector3(soft_body->m_faces[i].m_n[1]->m_x),
                        geometry::Vector3(soft_body->m_faces[i].m_n[2]->m_x));
                }
                return geometry::Facet(
                    geometry::Vector3(-soft_body->m_faces[i].m_normal),
                    geometry::Vector3(soft_body->m_faces[i].m_n[2]->m_x),
                    geometry::Vector3(soft_body->m_faces[i].m_n[1]->m_x),
                    geometry::Vector3(soft_body->m_faces[i].m_n[0]->m_x));
            }
        };
    }
}
#endif // PDPD_THINGS_FLEXURE

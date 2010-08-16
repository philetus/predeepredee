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
#include "../geometry3/Vector3.h"
#include "../geometry3/Transformation3.h"
#include "../geometry3/Facet.h"

namespace pdpd
{
    namespace things
    {
        class Flexure : public SoftThing
        {
        protected:            
            geometry3::Vector3 vertices[2][2];
            int resolution[2];
            int fixed_corners;
            
            // *** iterator over facets
            friend class FacetIterator;
            class FacetIterator : public util::Iterator<geometry3::Facet>
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
                virtual geometry3::Facet next()
                    { return flexure.get_facet(index++); }
            }; // FacetIterator

            
        public:
            Flexure(
                const geometry3::Vector3& v00,
                const geometry3::Vector3& v10,
                const geometry3::Vector3& v01,
                const geometry3::Vector3& v11,
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
                                
                soft_body->setTotalMass(mass);

                // *** adjust flexure stiffness
                btSoftBody::Material* material = soft_body->appendMaterial();
                material->m_kLST = 0.95; // linear stiffness coef [0,1]
                material->m_kAST = 0.95; // area / angular stiffness coef [0,1]
                material->m_kVST = 0.95; // volume stiffness coef [0,1]
                soft_body->generateBendingConstraints(2, material);
                
                // *** adjust soft body config
                soft_body->m_cfg.kDP = 0.3; // damping coefficient [0,1]
                soft_body->m_cfg.kCHR = 0.95; // rigid contact stiffness
                                              // (hardness?) [0,1]
                soft_body->m_cfg.kAHR = 0.95; // anchor stiffness 
                                              // (hardness?) [0,1]
                
                // *** soft body collision mask
                soft_body->m_cfg.collisions =
                    btSoftBody::fCollision::SDF_RS // rigid vs soft:
                                                   // (shape diameter function?)
                    //btSoftBody::fCollision::CL_RS // rigid vs soft: 
                                                    // cluster vs convex
                    | btSoftBody::fCollision::VF_SS; // soft vs soft: 
                                                     // vertex vs face
                    //| btSoftBody::fCollision::CL_SS // soft vs soft: 
                                                      // cluster vs cluster
                    //| btSoftBody::fCollision::CL_SELF; // soft body self
                                                         // collision

                return soft_body;
            }
            
            // *** thing interface
            void get_parent_frame(geometry3::Transformation3*) {}
            void get_gl_parent_frame(btScalar*) {}

            // *** atomic thing interface
            util::Iterator<geometry3::Vector3>* iter_vertices()
                { return NULL; }
            util::Iterator<geometry3::Facet>* iter_facets()
                { return new FacetIterator(*this); }
            
            geometry3::Facet get_facet(int index)
            {
                int i = index / 2;
                bool side = static_cast<bool>(index % 2);
                
                if(side)
                {
                    return geometry3::Facet(
                        geometry3::Vector3(soft_body->m_faces[i].m_normal),
                        geometry3::Vector3(soft_body->m_faces[i].m_n[0]->m_x),
                        geometry3::Vector3(soft_body->m_faces[i].m_n[1]->m_x),
                        geometry3::Vector3(soft_body->m_faces[i].m_n[2]->m_x));
                }
                return geometry3::Facet(
                    geometry3::Vector3(-soft_body->m_faces[i].m_normal),
                    geometry3::Vector3(soft_body->m_faces[i].m_n[2]->m_x),
                    geometry3::Vector3(soft_body->m_faces[i].m_n[1]->m_x),
                    geometry3::Vector3(soft_body->m_faces[i].m_n[0]->m_x));
            }
        };
    }
}
#endif // PDPD_THINGS_FLEXURE

/*  FlexureJoint.h
 *
 *  constrains two rigid nodes to approximate a flexure
 *  
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */
 
#ifndef PDPD_THINGS_FLEXURE_JOINT
#define PDPD_THINGS_FLEXURE_JOINT

#include "ConstraintThing.h"
#include "RigidThing.h"
#include "../util/PairIterator.h"
#include "../geometry3/Vector3.h"
#include "../geometry3/Transformation3.h"

#define PI_OVER_180 0.01745329251994329547 // deg to rad

namespace pdpd
{
    namespace things
    {
        class FlexureJoint : public ConstraintThing
        {
        protected:
            RigidThing* alpha;
            geometry3::Vector3 alpha_anchor0;
            geometry3::Vector3 alpha_anchor1;
            RigidThing* beta;
            geometry3::Vector3 beta_anchor0;
            geometry3::Vector3 beta_anchor1;
            
            btGeneric6DofConstraint* flex_constraint;
            Vector3 lower_angle_limit;
            Vector3 upper_angle_limit;
        public:
            FlexureJoint(
                RigidThing* lph,
                geometry3::Vector3& lph_nchr0,
                geometry3::Vector3& lph_nchr1,
                RigidThing* bt,
                geometry3::Vector3& bt_nchr0,
                geometry3::Vector3& bt_nchr1
            )
            :
            alpha(lph),
            alpha_anchor0(lph_nchr0),
            alpha_anchor1(lph_nchr1),
            beta(bt),
            beta_anchor0(bt_nchr0),
            beta_anchor1(bt_nchr1),
            lower_angle_limit(-5.0 * PI_OVER_180, -5.0 * PI_OVER_180, 1.0),
            upper_angle_limit(5.0 * PI_OVER_180, 5.0 * PI_OVER_180, -1.0)
            {
                // find midpoint between anchors for frame
                // TODO: take rotation into account
                geometry3::Vector3 a_off = 
                    (alpha_anchor1 - alpha_anchor0) * 0.5;
                geometry3::Vector3 a_mid = alpha_anchor0 + a_off;
                geometry3::Transformation3 alpha_frame;
                alpha_frame.setOrigin(a_mid);

                geometry3::Vector3 b_off = (beta_anchor1 - beta_anchor0) * 0.5;
                geometry3::Vector3 b_mid = beta_anchor0 + b_off;
                geometry3::Transformation3 beta_frame;
                beta_frame.setOrigin(b_mid);
                
                // build constraint
                flex_constraint = new btGeneric6DofConstraint(
                    *(alpha->get_rigid_body()),
                    *(beta->get_rigid_body()),
                    alpha_frame, beta_frame, true);

	            flex_constraint->setAngularLowerLimit(lower_angle_limit);
	            flex_constraint->setAngularUpperLimit(upper_angle_limit);
            }
            
            ~FlexureJoint()
            {
                if(flex_constraint != NULL)
                {
                    delete flex_constraint;
                    flex_constraint = NULL;
                }
            }
            
            btTypedConstraint* get_constraint() { return flex_constraint; }
            
            util::Iterator<geometry3::Vector3>* iter_vertices() 
            {
                return NULL;
            }
            
            util::Iterator<geometry3::Facet>* iter_facets() 
            {
                return NULL;
            }
            
            util::Iterator<RigidThing*>* iter_constrained()
            {
                return new PairIterator(alpha, beta);
            }
        };
    }
}
#endif // PDPD_THINGS_FLEXURE_JOINT

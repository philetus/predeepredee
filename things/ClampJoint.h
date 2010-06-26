/*  ClampJoint.h
 *
 *  clamps two rigid nodes together
 *  
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */
 
#ifndef PDPD_THINGS_CLAMP_JOINT
#define PDPD_THINGS_CLAMP_JOINT

#include "ConstraintThing.h"
#include "RigidThing.h"
#include "../util/PairIterator.h"
#include "../geometry/Vector3.h"
#include "../geometry/Transformation3.h"

namespace pdpd
{
    namespace things
    {
        class ClampJoint : public ConstraintThing
        {
        protected:
            RigidThing* alpha;
            geometry::Transformation3 alpha_frame;
            RigidThing* beta;
            geometry::Transformation3 beta_frame;
            
            btGeneric6DofConstraint* clamp_constraint;
            
        public:
            ClampJoint(
                RigidThing* lph,
                const geometry::Transformation3& lph_frm,
                RigidThing* bt,
                const geometry::Transformation3& bt_frm
            )
            :
            alpha(lph),
            alpha_frame(lph_frm),
            beta(bt),
            beta_frame(bt_frm)
            {
                
                // build constraint
                clamp_constraint = new btGeneric6DofConstraint(
                    *(alpha->get_rigid_body()),
                    *(beta->get_rigid_body()),
                    alpha_frame, beta_frame, true);

	            clamp_constraint->setAngularLowerLimit(Vector3(0, 0, 0));
	            clamp_constraint->setAngularUpperLimit(Vector3(0, 0, 0));
            }
            
            ~ClampJoint()
            {
                if(clamp_constraint != NULL)
                {
                    delete clamp_constraint;
                    clamp_constraint = NULL;
                }
            }
            
            btTypedConstraint* get_constraint() { return clamp_constraint; }
            
            util::Iterator<geometry::Vector3>* iter_vertices() 
            {
                return NULL;
            }
            
            util::Iterator<geometry::Facet>* iter_facets() 
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
#endif // PDPD_THINGS_CLAMP_JOINT

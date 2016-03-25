//
// File:	StandardLocallyActiveDataRefineTransactionFactory.h
// Package:	SAMRAI transfer
// Copyright:	(c) 1997-2005 The Regents of the University of California
// Revision:	$Revision: 697 $
// Modified:	$Date: 2005-11-03 12:27:48 -0800 (Thu, 03 Nov 2005) $
// Description:	Concrete factory to create standard copy and time transactions 
//              for locally-active data refine schedules. 
//

#ifndef included_xfer_StandardLocallyActiveDataRefineTransactionFactory
#define included_xfer_StandardLocallyActiveDataRefineTransactionFactory

#ifndef included_SAMRAI_config
#include "SAMRAI_config.h"
#endif
#ifndef included_hier_Box
#include "Box.h"
#endif
#ifndef included_hier_BoxOverlap
#include "BoxOverlap.h"
#endif
#ifndef included_hier_PatchLevel
#include "PatchLevel.h"
#endif
#ifndef included_tbox_Arena
#include "tbox/Arena.h"
#endif
#ifndef included_tbox_Pointer
#include "tbox/Pointer.h"
#endif
#ifndef included_tbox_Transaction
#include "tbox/Transaction.h"
#endif
#ifndef included_xfer_RefineClasses
#include "RefineClasses.h"
#endif
#ifndef included_xfer_LocallyActiveDataRefineTransactionFactory
#include "LocallyActiveDataRefineTransactionFactory.h"
#endif


namespace SAMRAI {
    namespace xfer {

/*!
 * @brief Concrete subclass of LocallyActiveDataRefineTransactionFactory<DIM> base 
 * class that allocates RefineCopyTransaction<DIM> and RefineTimeTransaction<DIM>
 * objects for a LocallyActiveDataRefineSchedule<DIM> object.
 * 
 * @see xfer::RefineCopyTransaction
 * @see xfer::RefineTimeTransaction
 * @see xfer::LocallyActiveDataRefineTransactionFactory
 */

template<int DIM> 
class StandardLocallyActiveDataRefineTransactionFactory 
: public LocallyActiveDataRefineTransactionFactory<DIM>
{
public:
   /*!
    * @brief Default constructor.
    */
   StandardLocallyActiveDataRefineTransactionFactory();

   /*!
    * @brief Virtual destructor.
    */
   virtual ~StandardLocallyActiveDataRefineTransactionFactory<DIM>();

   /*!
    * @brief Set the array of RefineClass::Data items used by the transactions.
    */
   void setRefineItems(const typename RefineClasses<DIM>::Data** refine_items,
                       int num_refine_items);

   /*!
    * @brief Clear the array of RefineClass::Data items used by the transactions.
    */
   void unsetRefineItems();

   /*!
    * @brief Set simulation time used by the refine time transaction objects.
    */
   void setTransactionTime(double fill_time);

   /*!
    * @brief Allocate an appropriate refine copy or time transaction object.
    * When time interpolation flag is passed as true a RefineTimeTransaction<DIM>
    * object will be created.  Otherwise, a RefineCopyTransaction<DIM> aill be
    * created.
    *
    * @param dst_level      tbox::Pointer to destination patch level.
    * @param src_level      tbox::Pointer to source patch level.
    * @param overlap        tbox::Pointer to overlap region between patches.
    * @param dst_patch      Integer index of destination patch in destination
    *                       patch level.
    * @param src_patch      Integer index of source patch in source patch level.
    * @param ritem_id       Integer index of RefineClass::Data item associated
    *                       with transaction.
    * @param box            Optional const reference to box defining region of 
    *                       refine transaction.  Default is an empty box.
    * use_time_interpolation  Optional boolean flag indicating whether the
    *                       refine transaction involves time interpolation.
    *                       Default is false.
    * @param pool           Optional pointer to memory pool from which the
    *                       refine transaction may be allocated. Default is null.
    */
   tbox::Pointer<tbox::Transaction>
   allocate(tbox::Pointer< hier::PatchLevel<DIM> > dst_level,
            tbox::Pointer< hier::PatchLevel<DIM> > src_level,
            tbox::Pointer< hier::BoxOverlap<DIM> > overlap,
            int dst_patch_id,
            int src_patch_id,
            int ritem_id,
            const hier::Box<DIM>& box = hier::Box<DIM>(),
            bool use_time_interpolation = false,
            tbox::Pointer<tbox::Arena> pool = (tbox::Arena *) NULL) const;

private:
   // The following two functions are not implemented
   StandardLocallyActiveDataRefineTransactionFactory(
      const StandardLocallyActiveDataRefineTransactionFactory<DIM>&);
   void operator=(const StandardLocallyActiveDataRefineTransactionFactory<DIM>&);

   const typename RefineClasses<DIM>::Data** d_refine_items;
   int d_num_refine_items;

};

}
}
#endif

#ifdef INCLUDE_TEMPLATE_IMPLEMENTATION
#include "StandardLocallyActiveDataRefineTransactionFactory.C"
#endif
#include "linear_sequence.h"
#include <mem.h>

typedef struct {
    LSQ_BaseTypeT *head;
    LSQ_IntegerIndexT size;
} LSQ;

typedef struct {
    LSQ_IntegerIndexT index;
    LSQ *handle;
} LSQ_Iterator;

LSQ_HandleT LSQ_CreateSequence(){
    LSQ *Mmas = malloc(sizeof(LSQ));
    Mmas->head = NULL;
    Mmas->size = 0;
    return ((LSQ_HandleT)Mmas);
}

void LSQ_DestroySequence(LSQ_HandleT handle){
    if (handle == LSQ_HandleInvalid) return;
    free((((LSQ*)(handle)))->head);
    free(((LSQ*)(handle)));
}

LSQ_IntegerIndexT LSQ_GetSize(LSQ_HandleT handle){
    if (handle != LSQ_HandleInvalid){
        return (((LSQ*)(handle))->size);
    }else{
        return 0;
    }
}

int LSQ_IsIteratorDereferencable(LSQ_IteratorT iterator){
    if      ((iterator != NULL) && (((LSQ_Iterator*)(iterator))->index >= 0) &&
            (((LSQ_Iterator*)(iterator))->index < ((LSQ_Iterator*)(iterator))->handle->size)){
        return 1;
    } else {
        return 0;
    }
}

int LSQ_IsIteratorPastRear(LSQ_IteratorT iterator){
    if ((iterator != NULL) && (((LSQ_Iterator*)(iterator))->index >=
            ((LSQ_Iterator*)(iterator))->handle->size)) {
        return 1;
    } else {
        return 0;
    }

}

int LSQ_IsIteratorBeforeFirst(LSQ_IteratorT iterator){
   if ((iterator != NULL) && (((LSQ_Iterator*)(iterator))->index < 0)){
        return 1;
    } else {
        return 0;
    }

}

LSQ_BaseTypeT* LSQ_DereferenceIterator(LSQ_IteratorT iterator){
    if (iterator == NULL){
        return NULL;
    }

    if (((LSQ_Iterator*)(iterator))->handle->head + ((LSQ_Iterator*)(iterator))->index){
        return 1;
    } else{
        return 0;
    }
}

LSQ_IteratorT LSQ_GetElementByIndex(LSQ_HandleT handle, LSQ_IntegerIndexT index){
    if (handle == LSQ_HandleInvalid) {
        return NULL;
    }
    LSQ_Iterator *titerator = malloc(sizeof(LSQ_Iterator));
    titerator->index = index;
    titerator->handle = ((LSQ*)(handle));
    return ((LSQ_IteratorT)titerator);
}

LSQ_IteratorT LSQ_GetFrontElement(LSQ_HandleT handle){
    if (handle == LSQ_HandleInvalid) {
        return (LSQ_HandleInvalid);
    }
    LSQ_Iterator *titerator = malloc(sizeof(LSQ_Iterator));
    titerator->index = 0;
    titerator->handle = ((LSQ*)(handle));
    return ((LSQ_IteratorT)titerator);
}

LSQ_IteratorT LSQ_GetPastRearElement(LSQ_HandleT handle){
    if (handle == LSQ_HandleInvalid) {
        return (LSQ_HandleInvalid);
    }
    LSQ_Iterator *titerator = malloc(sizeof(LSQ_Iterator));
    titerator->index = ((LSQ*)(handle))->size;
    titerator->handle = ((LSQ*)(handle));
    return ((LSQ_IteratorT)titerator);
}

void LSQ_DestroyIterator(LSQ_IteratorT iterator){
    free(((LSQ_Iterator*)(iterator)));
}

void LSQ_AdvanceOneElement(LSQ_IteratorT iterator){
    if (((LSQ_Iterator*)(iterator)) == NULL) return;
    ((LSQ_Iterator*)(iterator))->index++;
}

void LSQ_RewindOneElement(LSQ_IteratorT iterator){
    if (((LSQ_Iterator*)(iterator)) == NULL) return;
    ((LSQ_Iterator*)(iterator))->index--;
}

void LSQ_ShiftPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT shift){
    if (((LSQ_Iterator*)(iterator)) == NULL) return;
    ((LSQ_Iterator*)(iterator))->index += shift;
}

void LSQ_SetPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT pos){
    if (((LSQ_Iterator*)(iterator)) == NULL) return;
    ((LSQ_Iterator*)(iterator))->index = pos;
}

void LSQ_InsertFrontElement(LSQ_HandleT handle, LSQ_BaseTypeT element){
    if (((LSQ*)(handle)) == LSQ_HandleInvalid) return;
    ((LSQ*)(handle))->size++;
    ((LSQ*)(handle))->head = realloc(((LSQ*)(handle))->head, sizeof(LSQ_BaseTypeT) * ((LSQ*)(handle))->size);
    memmove(((LSQ*)(handle))->head + 1, ((LSQ*)(handle))->head, sizeof(LSQ_BaseTypeT) * (((LSQ*)(handle))->size - 1));
    *(((LSQ*)(handle))->head) = element;
}

void LSQ_InsertRearElement(LSQ_HandleT handle, LSQ_BaseTypeT element){
    if (((LSQ*)(handle)) == LSQ_HandleInvalid) return;
    ((LSQ*)(handle))->size++;
    ((LSQ*)(handle))->head = realloc(((LSQ*)(handle))->head, sizeof(LSQ_BaseTypeT) * ((LSQ*)(handle))->size);
    *(((LSQ*)(handle))->head + ((LSQ*)(handle))->size - 1) = element;
}

void LSQ_InsertElementBeforeGiven(LSQ_IteratorT iterator, LSQ_BaseTypeT newElement){
    if (((LSQ_Iterator*)(iterator)) == NULL) return;
    ((LSQ_Iterator*)(iterator))->handle->size++;
    ((LSQ_Iterator*)(iterator))->handle->head = realloc(((LSQ_Iterator*)(iterator))->handle->head,
                                                        sizeof(LSQ_BaseTypeT) * ((LSQ_Iterator*)(iterator))->handle->size);
    memmove(((LSQ_Iterator*)(iterator))->handle->head + ((LSQ_Iterator*)(iterator))->index + 1,
            ((LSQ_Iterator*)(iterator))->handle->head + ((LSQ_Iterator*)(iterator))->index,
            sizeof(LSQ_BaseTypeT) * (((LSQ_Iterator*)(iterator))->handle->size -((LSQ_Iterator*)(iterator))->index - 1));
    (*(((LSQ_Iterator*)(iterator))->handle->head + ((LSQ_Iterator*)(iterator))->index)) = newElement;
}

void LSQ_DeleteFrontElement(LSQ_HandleT handle){
    if (((LSQ*)(handle)) == LSQ_HandleInvalid) return;
    if (((LSQ*)(handle))->size == 0) return;
    ((LSQ*)(handle))->size--;
    ((LSQ*)(handle))->head++;
}

void LSQ_DeleteRearElement(LSQ_HandleT handle){
    if (((LSQ*)(handle)) == LSQ_HandleInvalid) return;
    if (((LSQ*)(handle))->size == 0) return;
    ((LSQ*)(handle))->size--;
}

void LSQ_DeleteGivenElement(LSQ_IteratorT iterator){
    if ((((LSQ_Iterator*)(iterator)) == NULL) || (!LSQ_IsIteratorDereferencable(iterator))) return;
    ((LSQ_Iterator*)(iterator))->handle->size--;
    memmove(((LSQ_Iterator*)(iterator))->handle->head + ((LSQ_Iterator*)(iterator))->index,
            ((LSQ_Iterator*)(iterator))->handle->head + ((LSQ_Iterator*)(iterator))->index + 1,
            sizeof(LSQ_BaseTypeT) * (((LSQ_Iterator*)(iterator))->handle->size - ((LSQ_Iterator*)(iterator))->index));
    ((LSQ_Iterator*)(iterator))->handle->head = realloc(((LSQ_Iterator*)(iterator))->handle->head,
                                             sizeof(LSQ_BaseTypeT) * (((LSQ_Iterator*)(iterator))->handle->size));
}
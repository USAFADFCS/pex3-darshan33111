/** pagequeue.c
 * ===========================================================
 * Name: C2C Darshan Kiran Koushik, 20 April 2026
 * Section: CS483 / M3 
 * Project: PEX3 - Page Replacement Simulator
 * Purpose: Implementation of the PageQueue ADT — a doubly-linked
 *          list for LRU page replacement.
 *          Head = LRU (eviction end), Tail = MRU end.
 * =========================================================== */
#include <stdio.h>
#include <stdlib.h>

#include "pagequeue.h"

/**
 * @brief Create and initialize a page queue with a given capacity
 */
PageQueue *pqInit(unsigned int maxSize) {
    // TODO: malloc a PageQueue, set head and tail to NULL,
    //       size to 0, maxSize to maxSize, and return the pointer
    PageQueue* newPQ = (PageQueue*)malloc(sizeof(PageQueue)*1);
    newPQ->head = NULL; 
    newPQ->tail = NULL; 
    newPQ->size = 0; 
    newPQ->maxSize = maxSize; 
    return newPQ;
}

/**
 * @brief Access a page in the queue (simulates a memory reference)
 */
long pqAccess(PageQueue *pq, unsigned long pageNum) {
    // TODO: Search the queue for pageNum (suggest searching tail->head
    //       so you naturally count depth from the MRU end).
    //
    //Empty List Case - MISS
        if(pq->size == 0) { 
            PqNode* next = (PqNode*)malloc(sizeof(PqNode)*1); 
            next->prev = NULL; 
            next->next = NULL; 
            next->pageNum = pageNum; 
            pq->head = next; 
            pq->tail = next;
            pq->size++; 
            return -1;
        }
    int currentPos = pq->size - 1; 
    PqNode* current = pq->tail; 
    int d = 0; 
    while(current->pageNum != pageNum && currentPos != 0){
        current = current->prev; 
        currentPos--; 
        d++; 
    }
    // HIT path (page found at depth d):
    //   - Remove the node from its current position and re-insert
    //     it at the tail (most recently used).
    //   - Return d.
    //
    if(current->pageNum == pageNum) { 
        //HIT at Tail Case 
        if (currentPos == pq->size - 1) { 
            //NOTHING
        }
        //Normal Case 
        else { 
            PqNode* temp = current;
            //head case 
            if(pq->head == temp) { 
                pq->head = temp->next; 
                if(pq->head != NULL) { 
                    pq->head->prev = NULL; 
                }
            }
            else { 
                (temp->prev)->next = temp->next; 
                (temp->next)->prev = temp->prev;  
            }
            temp->prev = pq->tail; 
            temp->next = NULL;
            pq->tail->next = temp; 
            pq->tail = temp; 
            
        }
        
        return d; 
    }
    // MISS path (page not found):
    //   - Allocate a new node for pageNum and insert it at the tail.
    //   - If size now exceeds maxSize, evict the head node (free it).
    //   - Return -1.
    if(currentPos == 0 && current->pageNum != pageNum) { 
        PqNode* next = (PqNode*)malloc(sizeof(PqNode)*1); 
        next->prev = NULL; 
        next->next = NULL; 
        next->pageNum = pageNum; 
        //Normal Case
        next->prev = pq->tail; 
        pq->tail->next = next; 
        pq->tail = next; 
        pq->size++; 
        if(pq->size > pq->maxSize)  {
            PqNode* temp = pq->head; 
            pq->head = pq->head->next; 
            free(temp); 
            if(pq->head != NULL) {
                pq->head->prev = NULL;
            }
            pq->size--; 
        }
    }
    
    return -1;
}

/**
 * @brief Free all nodes in the queue and reset it to empty
 */
void pqFree(PageQueue *pq) {
    // TODO: Walk from head to tail, free each node, then free
    //       the PageQueue struct itself.
    PqNode* current = pq->head; 
    while(current != NULL){
        PqNode* temp = current; 
        current = current->next; 
        free(temp); 
    }
    free(pq); 

}

/**
 * @brief Print queue contents to stderr for debugging
 */
void pqPrint(PageQueue *pq) {
    // TODO (optional): Print each page number from head to tail,
    //                  marking which is head and which is tail.
    //                  Useful for desk-checking small traces.
}

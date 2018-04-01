/** \addtogroup Middlewares
 * @{ */

/**
 * \defgroup Queue
 *
 * This module contains queue methods 
 * @{
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdint.h>

#define QUEUE_SIZE 100 /**< Queue size */

/**
 * @brief Enumerator of queue flags
 */
enum Queue_flag_e {
    QUEUE_FLAG_TXPRIMED = 0x01, /**< Queue flag for transmit byte */
    QUEUE_FLAG_RXOVERFLOW = 0x10, /**< Queue flag for receive overflow */
};

/**
 * @brief Queue_s struct which contains queue buffer, flags, count of readed
 * and written bytes
 */
struct Queue_s {
    uint16_t pRD; /**< Count of readded bytes */
    uint16_t pWR; /**< Count of written bytes */
    uint8_t q[QUEUE_SIZE]; /**< Queue buffer */
    uint8_t flag; /**< Queue flags */
};

/**
 * @brief Is queue full
 * @param q Instance of Queue_s
 * @return 
 */
uint8_t QueueFull(struct Queue_s *q);

/**
 * @brief Is queue empty
 * @param q Instance of Queue_s
 * @return 
 */
uint8_t QueueEmpty(struct Queue_s *q);

/**
 * @brief Place data as parameter to queue
 * @param q Instance of Queue_s
 * @param data Character which is placed to queue
 * @return 1 if operation is succesfull, 0 if queue is full
 */
uint8_t Enqueue(struct Queue_s *q, uint8_t data);

/**
 * @brief Receive byte from queue
 * @param q Instance of Queue_s
 * @param data Target buffer
 * @return 1 if operation is succesfull, 0 if queue is empty
 */
uint8_t Dequeue(struct Queue_s *q, uint8_t *data);

/**
 * @brief Set flag in queue
 * @param q Instance of Queue_s
 * @param flag Flag which must be set, instace of enum Queue_flag_e
 */
void SetFlag(struct Queue_s *q, enum Queue_flag_e flag);

/**
 * @brief Reset flag in queue
 * @param q Instance of Queue_s
 * @param flag Flag which must be reset, instace of enum Queue_flag_e
 */
void ResetFlag(struct Queue_s *q, enum Queue_flag_e flag);

/**
 * @brief Is flag active in queue
 * @param q Instance of Queue_s
 * @param flag Flag on which is question
 * @return 1 for active, 0 fer deactive
 */
uint8_t IsFlagActive(struct Queue_s *q, enum Queue_flag_e flag);

#endif /* QUEUE_H */

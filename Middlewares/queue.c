#include "queue.h"
#include <stdio.h>
#include <stdint.h>

uint8_t QueueFull(struct Queue_s *q)
{
    return (((q->pWR + 1) % QUEUE_SIZE) == q->pRD);
}

uint8_t QueueEmpty(struct Queue_s *q)
{
    return (q->pWR == q->pRD);
}

uint8_t Enqueue(struct Queue_s *q, uint8_t data)
{
    if (QueueFull(q))
        return 0;
    else {
        q->q[q->pWR] = data;
        q->pWR = ((q->pWR + 1) == QUEUE_SIZE) ? 0 : q->pWR + 1;
    }
    return 1;
}

uint8_t Dequeue(struct Queue_s *q, uint8_t *data)
{
    if (QueueEmpty(q))
        return 0;
    else {
        *data = q->q[q->pRD];
        q->pRD = ((q->pRD + 1) == QUEUE_SIZE) ? 0 : q->pRD + 1;
    }
    return 1;
}

void SetFlag(struct Queue_s *q, enum Queue_flag_e flag)
{
    q->flag |= flag;
}

void ResetFlag(struct Queue_s *q, enum Queue_flag_e flag)
{
    if (q->flag)
        q->flag = q->flag - flag;
}

uint8_t IsFlagActive(struct Queue_s *q, enum Queue_flag_e flag)
{
    return (((q->flag & flag) > 0) ? 1 : 0);
}

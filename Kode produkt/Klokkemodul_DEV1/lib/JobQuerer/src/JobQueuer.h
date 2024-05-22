#include <Arduino.h>
/**
 * @file JobQueuer.h
 * @author ESD210
 * @brief En virkelig hurtig måde at have en måde at sætte processoropgaver i kø... Virker ikke interrupted eller med managed stack :/ (Non Preemtable)
 * @version 0.1
 * @date 2024-04-09
 */

enum ExecutionStatus{UNSTARTED, RUNNING, DONE};

class Job{

    public:
    void (*func)();
    ExecutionStatus state = UNSTARTED;
    Job* next;
    uint16_t D_r;
    void Append(Job* input);
    Job(void (*functionToCall)());
};





namespace Queuer{
    extern Job* QueueHead;
    /**
     * @brief Sætter et job i kø, prioriteret efter D_r.
     * 
     * @param input job der skal afvikles
     * @param D_r Jobbets relative deadline 
     */
    void Queue(Job* input, uint16_t D_r);

    void Queue_INT(Job* input, uint16_t D_r);

    /**
     * @brief Starter løkken med taskhandleren
     * @note Non preemptive, og nok mest en state machine... men altså virkeren så virkeren.
     */
    void Begin();


    /**
     * @brief Flusher Jobkøen
     * 
     */
    void Flush();
}


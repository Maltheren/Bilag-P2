#include <JobQueuer.h>

/**
 ** Fælles definationer der bruges i h filen
*/

Job* Queuer::QueueHead = NULL; 


void Job::Append(Job* input){
    input->next = next;
    next = input;
}


void Queuer::Queue(Job* input, uint16_t D_r){
    cli();
    input->state = UNSTARTED;
    input->D_r = D_r;
    if(QueueHead == NULL){ //hvis der er en tom kø
        QueueHead = input;
        QueueHead->next = NULL;
        sei();
        return;
    }
    Job* current = QueueHead;
    while (current->D_r < input->D_r && current->next != NULL)
    {
        current = current->next;
    }
    current->Append(input);
    sei();
}

void Queuer::Queue_INT(Job* input, uint16_t D_r){
    input->state = UNSTARTED;
    input->D_r = D_r;
    if(QueueHead == NULL){ //hvis der er en tom kø
        QueueHead = input;
        QueueHead->next = NULL;
        return;
    }
    Job* current = QueueHead;
    while (current->D_r < input->D_r && current->next != NULL)
    {
        current = current->next;
    }
    current->Append(input);
}


Job::Job(void (*functionToCall)()){
    func = functionToCall;
    state = UNSTARTED;
}

#define debugPCHIGH(pin) PORTC  |=  (1<<pin) //@brief sætter PORTC pin HIGH
#define debugPCLOW(pin)  PORTC  &= ~(1<<pin) //@brief sætter PORTC pin LOW

void Queuer::Begin(){ //*SKAL GÅ STÆRRRRKT
    while (1)
    {
        if(QueueHead != NULL){
            cli();
            if(QueueHead->state == UNSTARTED){
                QueueHead->state = RUNNING;
                sei();
                digitalWrite(A3, HIGH);
                QueueHead->func(); //Kører funktionen
                digitalWrite(A3, LOW);
                cli();
                QueueHead->state = DONE;
            }
            QueueHead = QueueHead->next;
            sei();
        }
        cli();
        if(QueueHead->next == QueueHead){ //hvis svinet sætter sig selv til næste.
            QueueHead->next = NULL;
        }
        sei();
    }
}
void Queuer::Flush(){
    QueueHead = NULL;
    
}
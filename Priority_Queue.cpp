#include "Priority_Queue.h"

using namespace std;

Priority_Queue::Priority_Queue()
{
    heap = NULL;
    handle = NULL;
    max_size = 0;
    curr_size = 0;
    curr_id = 0;
}

Priority_Queue::Priority_Queue(int size)
{
    heap = new Contestant*[size];
    max_size = size;
    curr_size = 0;
    handle = new int[size];
    curr_id = 0;
    /* At the start, handle is initialized to an array of -1s */
    for (int i = 0; i < size; i++) handle[i] = -1;
}

Priority_Queue::~Priority_Queue()
{
    delete[] heap;
    delete[] handle;
}

Contestant** Priority_Queue::get_heap()
{
    return heap;
}

int* Priority_Queue::get_handle()
{
    return handle;
}

int Priority_Queue::get_max_size()
{
    return max_size;
}

int Priority_Queue::get_curr_size()
{
    return curr_size;
}

void Priority_Queue::set_curr_size(int new_size)
{
    curr_size = new_size;
}

/** 
 * Runs in O(1) using the handle array 
 *  Return the contestant if contestant is in the heap
 *  Otherwise, return NULL
**/
Contestant* Priority_Queue::findContestant(int k)
{
    // index i stores the index of where the person with id i is in the heap
    if (k <= curr_size && handle[k - 1] >= 0) return heap[handle[k - 1]];
    else return NULL;
}

/** 
 * Inserts new contestant into heap
 * 1) Create contestant
 * 2) Add contestant to end of heap
 * 3) Min-heapify to maintain heap property   
**/
char Priority_Queue::insertContestant(int k, int s)
{
    Contestant* new_contestant = new Contestant(k, s);
    if (max_size <= curr_size) return 'b';
    if (findContestant(k) != NULL) return 'c';
    handle[k - 1] = curr_size;
    heap[curr_size] = new_contestant;
    min_heapify((curr_size - 1)/2);
    curr_size++;
    return 'a';
}

/**
 * Swaps contestants at index1 and index2
 * Also swaps the values of the handles at id1 and id2
**/
void Priority_Queue::swap(int index1, int index2)
{
    Contestant* temp = heap[index1];
    heap[index1] = heap[index2];
    heap[index2] = temp;
    handle[heap[index1]->get_id() - 1] = index1;
    handle[heap[index2]->get_id() - 1] = index2;
}

/**
 * If the left or right is smaller, swap current and smaller or the two
 * Then perform min_heapify on the smallest
 * Return index of position of newly inserted item
**/
void Priority_Queue::min_heapify(int pos)
{
    int smallest = pos;
    int left = pos*2 + 1;
    int right = pos*2 + 2;
    if (left < curr_size && heap[pos]->get_points() > heap[left]->get_points())
    {
        smallest = left;
    }
    if (right < curr_size && heap[smallest]->get_points() > heap[right]->get_points())
    {
        smallest = right;
    }
    if (smallest != pos)
    {
        swap(smallest, pos);
        min_heapify(smallest);
    }
}

Contestant* Priority_Queue::eliminateWeakest()
{
    if (curr_size == 0)
    {
        return NULL;
    }
    else
    {
        Contestant* temp = heap[0];
        curr_size--;
        swap(0, curr_size);
        handle[heap[curr_size]->get_id() - 1] = -1;
        heap[curr_size] = NULL;
        min_heapify((curr_size - 1)/2);
        return temp;
    }
}

Contestant* Priority_Queue::earnPoints(int k, int p)
{
    if (findContestant(k) == NULL)
    {
        return NULL;
    }
    else
    {
        findContestant(k)->set_points(findContestant(k)->get_points() + p);
        min_heapify((curr_size - 1)/2);
        return findContestant(k);
    }
}

Contestant* Priority_Queue::losePoints(int k, int p)
{
    if (findContestant(k) == NULL)
        {
            return NULL;
        }
    else
    {
        findContestant(k)->set_points(findContestant(k)->get_points() - p);
        min_heapify((curr_size - 1)/2);
        return findContestant(k);
    }
}

void Priority_Queue::showContestants(ofstream &output)
{
    for (int i = 0; i < curr_size; i++)
    {
        output << "Contestant <" << heap[i]->get_id() << "> in extended heap location <" <<
        i + 1 << "> with score <" << heap[i]->get_points() << ">." << endl;
    }
}

void Priority_Queue::showHandles(ofstream &output)
{
    for (int i = 0; i < max_size; i++)
    {
        if (handle[i] == -1)
        {
            output << "There is no Contestant <" << i + 1<< "> in the extended heap: " <<
            "handle[<" << i + 1 << ">] = -1." << endl;
        }
        else
        {
            output << "Contestant <" << i + 1<< "> stored in extended heap location <" << 
            handle[i] + 1<< ">." << endl;
        }
    }
}

int Priority_Queue::showLocation(int k)
{
    if (handle[k - 1] == -1)
    {
        return -1;
    }
    return handle[k - 1];
}

Contestant* Priority_Queue::crownWinner()
{
    while (curr_size > 1)
    {
        eliminateWeakest();
    }
    return eliminateWeakest();
}  

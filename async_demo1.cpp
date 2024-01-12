#include<iostream>
#include<future>

/*
    Option 1 : One after the other . always complete one ting before starting 
    the next line.

name : single thread technique 
    Option 2 : I will complete all task in such a way that i pratically start
    all of them at the same time but keep jugling them basrd on some criteria 
name : multi threading 

    Option 3: map number of task amongst number of "workers"

name : parallel execution 
    Option 4: start a task either deligated to another worker or do it your self
    after some time


    if someone else is doing a task monitor it wait for the work to be done 
    take follow up actions accordingly
name : asynchronous execution 
*/

/* 
 2 task 
 calculate factorial of 5
 calculate square of a number given by user
*/
int square(std::future<int>& ft){
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout<<"\nHello from square.I have started my work!\n";
    int number=ft.get();
    return number*number;
}

int factorial(int number){
    std::this_thread::sleep_for(std::chrono::seconds(3));
    if(number<0){

        throw std::runtime_error("");
    }
    else if(number==0 || number==1){
        return 1;
    }
    else{
        return number*factorial(number-1);
    }
    
}


int main(){

    // step 1 : make a promise 
    std::promise<int> pr;

    //step 2 : A future linked to the promise 
    std::future<int> ft=pr.get_future();

    /*
        OS : launch sqaure(if possible as a new thread)    
    */
    std::future<int> result_ft=std::async(std::launch::async,&square,std::ref(ft));
    
    int val=0;
    std::cin>>val;
    pr.set_value(val);
    std::cout<<"\nThere is normal :"<<factorial(5);
    std::cout<<"\nResult of factorial is :"<<result_ft.get();
}

/*
    client_server architecture


    future-promise-model


    square calculation 

    Main needs to delegate the task of sqaure calculation

    ---> a new thread for square will be registered with OS 

*/
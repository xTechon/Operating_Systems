#include "banker.h"

Request::Request(void){};

// Class Constructor Definition
Request::Request(Banker *mnk) {
  // copies the state into the Request Class Object
  this->man = *mnk;
  // Set the request matrix to the same size as the original state
  this->ReqVect = vector_t::Constant(this->man.getCols(), 0);
  this->prev = nullptr;
}

// In case I know which proccess the request belongs in advance
Request::Request(Banker *mnk, int proc) {
  // copies the state into the Request Class Object
  this->man = *mnk;
  // Set the request matrix to the same size as the original state
  this->ReqVect = vector_t::Constant(this->man.getCols(), 0);
  this->proccess = proc;
  this->prev = nullptr;
}

// Preffered Constructor
Request::Request(Banker *mnk, vector_t req, int proc) {
  // copies the state into the Request Class Object
  this->man = *mnk;
  this->man.calcNeed();
  // Set the request matrix to the vector passed to it
  this->reqPush = false;
  this->ReqVect = req;
  this->proccess = proc;
  this->prev = nullptr;
}
Request::Request(vector_t req, int proc) {
  // Set the request matrix to the vector passed to it
  this->ReqVect = req;
  this->proccess = proc;
  this->prev = nullptr;
}

Request::Request(Request *prev, vector_t req, int proc) {
  // Set the request matrix to the vector passed to it
  this->ReqVect = req;
  this->proccess = proc;
  this->prev = prev;
}

// copy constructor
Request::Request(Request const &source) {
  this->ReqVect = source.ReqVect;
  this->proccess = source.proccess;
  this->prev = source.prev;
  this->man = source.man;
}

int Request::pushReq() {
  std::cout << "REQUEST: P" << proccess << ": " << ReqVect << std::endl;
  // STEP 1: If Reqi <= Needi goto step 2, otherwise error
  vector_t test1 =
      man.Need.row(this->proccess) - ReqVect; // To hold Needi - Reqi
  std::cout << "NEEDi - REQ = " << test1 << std::endl;
  // if Reqi <= Needi, than Needi - Reqi >= 0
  if (test1.minCoeff() >= 0) {
    // STEP 2: if Reqi <= Availi goto step 3, Pi must wait because res not avail
    vector_t test2 = man.Avail - ReqVect;
    std::cout << "Avail - Req:\n" << test2 << std::endl;
    if (test2.minCoeff() >= 0) {
      // STEP 3: Prettend to Allocate req
      //  Avail = Avail - Req
      man.Avail = test2;
      //  Alloci = Alloci + Reqi
      man.Alloc.row(proccess) = man.Alloc.row(proccess) + ReqVect;
      //  Needi = Needi - Reqi
      man.Need.row(proccess) = test1;
      reqPush = true;
      return 1;
    } else {
      std::cout << "REQUEST NOT GRANTED: NOT ENOUGH RESOURCES AVAILABLE"
                << std::endl;
      return 0;
    }
  } else {
    std::cout << "ERROR: REQUEST GREATER THAN NEED" << std::endl;
    return -1;
  }
}

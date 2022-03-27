#include<iostream>
#include<string>
#include<iomanip>
#include<exception>
#include<fstream>
#include<sstream>

using namespace std;

typedef string Elem;
string currentMember_ID;
string currentAdmin_ID;
string input_username;
string input_password;

void to_lowercase(string& name){ // function to be called later when making all words lower-cased
    for(int i=0;name[i]!='\0';i++){
        if (name[i] >= 'A' && name[i] <= 'Z')
            name[i] = name[i] + 32;
    }
}

class Node // for doublylinkedlists (list of bookings/sessions and registered members) inside big linked lists
{
	public:
		Node(): next(NULL), prev(NULL)
		{}
		Node(Elem elem) : elem(elem),next(NULL), prev(NULL)
		{}
        Elem elem; // data element
        Node* next; // link (pointer) to the next Node
        Node* prev; // link (pointer) to the previous Node
        friend class DoublyLinkedList;
};
//============================================================
class DoublyLinkedList
{
	public:
		DoublyLinkedList (); // empty list constructor
		~DoublyLinkedList (); // destructor to clean up all nodes
		bool empty() const; // is list empty?
		const Elem& front() const; // get the value (element) from front Node of list
		const Elem& back() const;  // get the value (element) from last Node of the List 
		void addBefore(Node *ptr, const Elem& elem);	 //add a new node before ptr
		void addFront(const Elem& elem); // add a new node to the front of list
		void addBack(const Elem & elem); //add a new node to the back of the list
		void removeFront(); // remove front node from list
		void removeBack();  // remove last node from list
		void display() const;	// display all element of the list
		bool checkElem(string) const; // check what element it indicates
        int size() const; // check the size
        void remove();
        Node* head;  // pointer to the head of List
        Node* tail;  // pointer to the tail of List
};

//============================================================
DoublyLinkedList::DoublyLinkedList () // constructor
{
	this->head = new Node();
	this->tail = new Node();
	this->head->next = tail;
	this->tail->prev = head;
}
//============================================================
DoublyLinkedList::~DoublyLinkedList () // destructor to clean up all nodes
{
	while(!empty())
		removeFront();
}
//============================================================
bool DoublyLinkedList::empty() const // is list empty?
{
	return this->head->next == tail;
}
//============================================================
const Elem& DoublyLinkedList::front() const // get front element
{
	if(!empty())
		return this->head->next->elem;
	else
		throw runtime_error("List is Empty");
}
//============================================================
const Elem& DoublyLinkedList::back() const // get front element
{
	if(!empty())
		return this->tail->prev->elem;
	else
		throw runtime_error("List is Empty");
}
//============================================================
void DoublyLinkedList::addBefore(Node *ptr, const Elem& elem) // adding element to be called inside others
{
	Node *tmp = new Node(elem);
	tmp->next = ptr;
	tmp->prev = ptr->prev;
	ptr->prev->next = tmp;
	ptr->prev=tmp;
}
//============================================================
void DoublyLinkedList::addFront(const Elem& elem) // add to front of list
{
	addBefore(this->head->next, elem);
}
//============================================================
void DoublyLinkedList::addBack(const Elem& elem) // add to Back of the list
{
	addBefore(this->tail, elem);
}
//============================================================
void DoublyLinkedList::removeFront() // remove front item from list
{
	if(!empty())
	{
		Node *tmp = this->head->next;
		this->head->next = tmp->next;
		tmp->next->prev = head;
		delete tmp;
	}
}
//============================================================
void DoublyLinkedList::removeBack() // remove last item from list
{
	if(!empty())
	{
		Node *tmp = this->tail->prev;
		this->tail->prev = tmp->prev;
		tmp->prev->next = tail;
		delete tmp;
	}
}
//============================================================
void DoublyLinkedList::display() const // display linked-list in the form of [ | | ] etc
{
	Node *curr=head;

	curr=head;
	while(curr!=NULL)
	{
        if (curr == head) cout<<"[";
        else if(curr == tail) cout<<"]";
		else
        cout<<"|"<<curr->elem<<"|";
		curr=curr->next;
	}
}
//============================================================
bool DoublyLinkedList::checkElem(string a) const{ // check what element it indicates
	Node *curr = head;
	while(curr!=NULL){
		if (curr->elem == a)
			return true;
		else
			curr=curr->next;
	}
	return false;
}
//============================================================
int DoublyLinkedList::size() const{ // check the size 
    int size=0;
    Node *curr = head;
    
    while(curr!=NULL){
        size++;
        curr = curr->next;
    }
    
    return size;
}




//MEMBER CLASS
//========================================================================================================================
class Member 
{
	public: 
		string member_ID, first_name, last_name, username, password;
		DoublyLinkedList list_of_bookings; // list of bookings from the Member Class implemented as a linked list
    
		Member(string& member_ID, string& first_name, string& last_name, string& username, string& password, DoublyLinkedList& bookings); // constructor
		Member();
};

Member::Member()
{
	member_ID = "";
	first_name = "";
	last_name = "";
	username = "";
	password = "";
	list_of_bookings = DoublyLinkedList(); 
}

Member::Member(string& member_ID, string& first_name, string& last_name, string& username, string& password, DoublyLinkedList& bookings)
{
	this->member_ID = member_ID;
	this->first_name = first_name;
	this->last_name = last_name;
	this->username = username;
	this->password = password;
	this->list_of_bookings = bookings; 
}


class MemberNode
{
	public:
        Member elem;
        MemberNode* next;
        MemberNode* prev;
        friend class MemberLinkedList;
		MemberNode(): next(NULL), prev(NULL)
		{}
		MemberNode(Member elem): elem(elem), next(NULL), prev(NULL)
		{}
};

class MemberLinkedList
{
    public:
        MemberNode* head;
        MemberNode* tail;
		MemberLinkedList();
		~MemberLinkedList();
		const Member& front() const;
		const Member& back() const;
		void addBefore(MemberNode *ptr, const Member& elem);
		void addFront(const Member& elem);
		void addBack(const Member& elem);
		void removeFront();
		void removeBack();
        bool empty() const;
};
//============================================================
MemberLinkedList::MemberLinkedList() // constructor
{
	this->head = new MemberNode();
	this->tail = new MemberNode();
	head->next = tail;
	tail->prev = head;
}
//============================================================
MemberLinkedList::~MemberLinkedList() // deconstructor
{
	while (!empty())
		removeFront();
	delete this->head;
	delete this->tail;
}
//============================================================
const Member& MemberLinkedList::front() const // elem in front
{
	return this->head->next->elem;
}
//============================================================
const Member& MemberLinkedList::back() const // elem in back
{
	return this->tail->prev->elem;
}
//============================================================
void MemberLinkedList::addBefore(MemberNode *ptr, const Member& elem) // adding element to be called inside others
{
	MemberNode *pointer = new MemberNode(elem);
	pointer->next = ptr;
	pointer->prev = ptr->prev;
	ptr->prev->next = pointer;
	ptr->prev = pointer;
}
//============================================================
void MemberLinkedList::addFront(const Member& elem) // add in front
{
	addBefore(this->head->next, elem);
}
//============================================================
void MemberLinkedList::addBack(const Member& elem) // add in back
{
	addBefore(this->tail, elem);
}
//============================================================
void MemberLinkedList::removeFront() // remove front item from list
{
	if (!empty())
	{
		MemberNode *old = this->head->next; 
		this->head->next = old->next;
		old->next->prev = head; 
		delete old;
	}
}
//============================================================
void MemberLinkedList::removeBack() // remove last item from list
{
	if (!empty())
	{
		MemberNode *old = this->tail->prev; 
		this->tail->prev = old->prev;
		old->prev->next = tail;
		delete old;
	}
}
//============================================================
bool MemberLinkedList::empty() const{ // is it empty?
    return (this->head->next == tail);
}




//ADMIN CLASS
//========================================================================================================================
class Admin
{
	public: 
		string admin_ID, first_name, last_name, username, password; 
		Admin(string& admin_ID, string& first_name, string& last_name, string& username, string& password); // constructor
		Admin();

        string get_admin_ID(){				return admin_ID;}
        string get_firstname(){				return first_name;}
        string get_lastname(){				return last_name;}
        string get_username(){				return username;}
        string get_password(){				return password;}
};


Admin::Admin() //Empty admin constructor
{
	admin_ID = "";
	first_name = "";
	last_name = "";
	username = "";
	password = "";
}

Admin::Admin(string& admin_ID, string& first_name, string& last_name, string& username, string& password) //Admin constructor
{
	this->admin_ID = admin_ID;
	this->first_name = first_name;
	this->last_name = last_name;
	this->username = username;
	this->password = password; 
}

//AdminNode class for AdminLinkedList
class AdminNode 
{
	public:
		AdminNode(): next(NULL), prev(NULL)
		{}
		AdminNode(Admin elem): elem(elem), next(NULL), prev(NULL)
		{}
        Admin elem;
        AdminNode* next;
        AdminNode* prev;
        friend class AdminLinkedList;
};

//AdminLinkedList class
class AdminLinkedList
{
	public:
		AdminLinkedList();
		~AdminLinkedList();
		const Admin& front() const;
		const Admin& back() const;
		void addBefore(AdminNode *ptr, const Admin& elem);
		void addFront(const Admin& elem);
		void addBack(const Admin& elem);
		void removeFront();
		void removeBack();
        bool empty() const;
        AdminNode* head;
        AdminNode* tail;
};
//============================================================
AdminLinkedList::AdminLinkedList() // constructor
{
	this->head = new AdminNode();
	this->tail = new AdminNode();
	head->next = tail;
	tail->prev = head;
}
//============================================================
AdminLinkedList::~AdminLinkedList() // destructor
{
	while (!empty())
		removeFront();
	delete this->head;
	delete this->tail;
}
//============================================================
const Admin& AdminLinkedList::front() const // elem in front
{
	return head->next->elem;
}
//============================================================
const Admin& AdminLinkedList::back() const // elem in back
{
	return tail->prev->elem;
}
//============================================================
void AdminLinkedList::addBefore(AdminNode *ptr, const Admin& elem) // add elem to be called in others
{
	AdminNode *pointer = new AdminNode(elem); 
	pointer->next = ptr;
	pointer->prev = ptr->prev;
	ptr->prev->next = pointer;
	ptr->prev = pointer;
}
//============================================================
void AdminLinkedList::addFront(const Admin& elem) // add in front
{
	addBefore(this->head->next, elem);
}
//============================================================
void AdminLinkedList::addBack(const Admin& elem) // add in back
{
	addBefore(this->tail, elem);
}
//============================================================
void AdminLinkedList::removeFront() // remove front item from list
{
	if (!empty())
	{
        AdminNode *old = this->head->next; 
        this->head->next = old->next; 
        old->next->prev = head; 
        delete old;
	}
}
//============================================================
void AdminLinkedList::removeBack() // remove last item from list
{
	if (!empty())
	{
		AdminNode *old = this->tail->prev;
		this->tail->prev = old->prev;
		old->prev->next = tail;
		delete old;
	}
}
//============================================================
bool AdminLinkedList::empty() const{ // is it empty?
    return(this->head->next == tail);
}





// FITNESS CLASS
//========================================================================================================================
class Fitness
{
	public: 
		string class_ID, class_name;
		DoublyLinkedList list_of_sessions;
		Fitness(string& class_ID, string& class_name, DoublyLinkedList& list_of_sessions); 
		Fitness();

        string get_class_ID(){				return class_ID;}
        string get_class_name(){			return class_name;}
};

Fitness::Fitness() //Fitness empty constructor
{
	class_ID = "";
	class_name = "";
	list_of_sessions = DoublyLinkedList();
}

Fitness::Fitness(string& class_ID, string& class_name, DoublyLinkedList& list_of_sessions) //Fitness constructor
{
	this->class_ID = class_ID;
	this->class_name = class_name;
	this->list_of_sessions = list_of_sessions; 
}

//FitnessNode class for FitnessLinkedList
class FitnessNode
{
	public:
        Fitness elem;
        FitnessNode* next;
        FitnessNode* prev;
        friend class FitnessLinkedList;
		FitnessNode(): next(NULL), prev(NULL)
		{}
		FitnessNode(Fitness elem): elem(elem), next(NULL), prev(NULL) 
		{}
};

//FitnessLinkedList class 
class FitnessLinkedList
{
	public:
        FitnessNode* head;
        FitnessNode* tail;
		FitnessLinkedList();
		~FitnessLinkedList();
		const Fitness& front() const;
		const Fitness& back() const;
		void addBefore(FitnessNode *ptr, const Fitness& elem);
		void addFront(const Fitness& elem);
		void addBack(const Fitness& elem);
		void removeFront();
		void removeBack();
        bool empty() const;
};
//============================================================
FitnessLinkedList::FitnessLinkedList() // constructor
{
	head = new FitnessNode;
	tail = new FitnessNode;
	head->next = tail;
	tail->prev = head;
}
//============================================================
FitnessLinkedList::~FitnessLinkedList() // deconstructor
{
	while (!empty())
		removeFront();
	delete this->head;
	delete this->tail;
}
//============================================================
const Fitness& FitnessLinkedList::front() const // elem in front
{
	return head->next->elem;
}
//============================================================
const Fitness& FitnessLinkedList::back() const // elem in back
{
	return tail->prev->elem; 
}
//============================================================
void FitnessLinkedList::addBefore(FitnessNode *ptr, const Fitness& elem) // add elem to be used in others
{
	FitnessNode *pointer = new FitnessNode(elem);//고쳤음
	pointer->next = ptr;
	pointer->prev = ptr->prev;
	ptr->prev->next = pointer;
	ptr->prev = pointer;
}
//============================================================
void FitnessLinkedList::addFront(const Fitness& elem) // add elem in front
{
	addBefore(this->head->next, elem);
}
//============================================================
void FitnessLinkedList::addBack(const Fitness& elem) // add elem in back
{
	addBefore(this->tail, elem);
}
//============================================================
void FitnessLinkedList::removeFront() // remove front item from list
{
	if (!empty())
	{
        FitnessNode *old = this->head->next; 
        this->head->next = old->next; 
        old->next->prev = head; 
        delete old;
	}
}
//============================================================
void FitnessLinkedList::removeBack() // remove last item from list
{
	if (!empty())
	{
		FitnessNode *old = this->tail->prev;
		this->tail->prev = old->prev;
		old->prev->next = tail;
		delete old;
	}
}
//============================================================
bool FitnessLinkedList::empty() const{ // is it empty?
    return (this->head->next == tail);
}







//SESSION CLASS
//========================================================================================================================
class Session
{
	public: 
		string session_ID,class_ID,max_cap,session_date,session_time,room_number;
		DoublyLinkedList list_of_registered_members;
    
		Session(string& session_ID,string& class_ID,string& max_cap,string& session_date,string& session_time,string& room_number,DoublyLinkedList& list_of_registered_members);
		Session();

        string get_session_ID(){
            return session_ID;
        }
        string get_class_ID(){
            return class_ID;
        }
        string get_max_cap(){
            return max_cap;
        }
        string get_session_date(){
            return session_date;
        }
        string get_session_time(){
            return session_time;
        }
        string get_room_number(){
            return room_number;
        }
};

Session::Session() //Session empty constructor
{
	session_ID = "";
	class_ID = "";
	max_cap = "";
	session_date = "";
	session_time = "";
	room_number = "";
	list_of_registered_members = DoublyLinkedList();
}

//Session constructor
Session::Session(string& session_ID, string& class_ID, string& max_cap, string& session_date, string& session_time, string& room_number, DoublyLinkedList& list_of_registered_members )
{
    this->session_ID = session_ID;
    this->class_ID =class_ID;
    this->max_cap =max_cap;
    this->session_date =session_date;
    this->session_time =session_time;
    this->room_number = room_number;
    this->list_of_registered_members =list_of_registered_members;
}

//SessionNode class for SessionLinkedList
class SessionNode
{
	public:
		SessionNode(): next(NULL), prev(NULL)
		{}
		SessionNode(Session elem): elem(elem), next(NULL), prev(NULL)
		{}
        Session elem;
        SessionNode* next;
        SessionNode* prev;
        friend class SessionLinkedList;
};

//SessionLinkedList class
class SessionLinkedList
{
    public:
		SessionLinkedList();
		~SessionLinkedList();
		const Session& front() const;
		const Session& back() const;
		void addBefore(SessionNode *ptr, const Session& elem);
		void addFront(const Session& elem);
		void addBack(const Session& elem);
		void removeFront();
		void removeBack();
        bool empty() const;
        SessionNode* head;
        SessionNode* tail;
};
//============================================================
SessionLinkedList::SessionLinkedList(){ // constructor

	this->head = new SessionNode();
	this->tail = new SessionNode();
	head->next = tail;
	tail->prev = head;
}
//============================================================
SessionLinkedList::~SessionLinkedList() // destructor
{
	while (!empty())
		removeFront();
	delete this->head;
	delete this->tail;
}
//============================================================
const Session& SessionLinkedList::front() const // elem in front
{
	return head->next->elem;
}
//============================================================
const Session& SessionLinkedList::back() const // elem in back
{
	return tail->prev->elem;//고쳤음
}
//============================================================
void SessionLinkedList::addBefore(SessionNode *ptr, const Session& elem) // add elem to be used in others
{
	SessionNode *pointer = new SessionNode(elem);
	pointer->next = ptr;
	pointer->prev = ptr->prev;
	ptr->prev->next = pointer;
	ptr->prev = pointer;
}
//============================================================
void SessionLinkedList::addFront(const Session& elem) // add elem in front
{
	addBefore(this->head->next, elem);
}
//============================================================
void SessionLinkedList::addBack(const Session& elem) // add elem in back
{
	addBefore(this->tail, elem);
}
//============================================================
void SessionLinkedList::removeFront() // remove front item from list
{
	if (!empty())
	{
        SessionNode *old = this->head->next; 
        this->head->next = old->next; 
        old->next->prev = head; 
        delete old;
	}
}
//============================================================
void SessionLinkedList::removeBack() // remove last item from list
{
	if (!empty())
	{
        SessionNode *old = this->tail->prev;
        this->tail->prev = old->prev;
        old->prev->next = tail;
        delete old;
	}
}
//============================================================
bool SessionLinkedList::empty() const{ // is it empty?
    return(this->head->next == tail);
}






// calling linked lists to be used below 
//========================================================================================================================
AdminLinkedList admin_linked_list;
MemberLinkedList member_linked_list;
FitnessLinkedList fitness_linked_list;
SessionLinkedList session_linked_list;


// LOAD FILES 
//========================================================================================================================
void load_admin(string path) // load admin file
{
    ifstream file(path);
    string line;
    getline(file, line); // skip the first unnecessary line
    string admin_ID, first_name, last_name, username, password, admin;
        while (getline(file, line))
        {
            stringstream ss(line);
            getline(ss, admin_ID, ','); // take a variable/value one by one separated by comma
            getline(ss, first_name, ',');
            getline(ss, last_name, ',');
            getline(ss, username, ',');
            getline(ss, password, ',');
            admin_linked_list.addBack(Admin(admin_ID, first_name,last_name, username, password));
        }
    file.close(); // close the file
}

void load_members(string path) // load member file
{
    ifstream file(path);
    string line;
    getline(file, line); // skip the first unnecessary line
    string member_ID,first_name,last_name,username,password,bookings;

        while (getline(file, line))
        {
            stringstream ss(line);
            getline(ss, member_ID, ','); // take a variable/value one by one separated by comma
            getline(ss, first_name, ',');
            getline(ss, last_name, ',');
            getline(ss, username, ',');
            getline(ss, password, ',');
            getline(ss, bookings,'\n');
            DoublyLinkedList list_bookings; // bookings list inside the member list
            
            for(int i = 0; i<bookings.size(); i++)
            {
                if(bookings[i]>=49&&bookings[i]<=57)
                {
                    string s(1,bookings[i]);
                    list_bookings.addBack(s);
                }
            }
            member_linked_list.addBack(Member(member_ID,first_name,last_name,username,password,list_bookings));
        }

    file.close(); // close the file
}


void load_fitness(string path) // load fitness file
{
    ifstream file(path);
    string line;
    getline(file, line); // skip the first unnecessary line
    string class_ID,class_name,session;

        while (getline(file, line))
        {
            stringstream ss(line);
            getline(ss, class_ID, ','); // take a variable/value one by one separated by comma
            getline(ss, class_name, ',');
            getline(ss, session,'\n');
            DoublyLinkedList list_of_sessions; // session list inside the member list
            if(session.size()>2)
            {
                stringstream sess(session);
                string e;
                while(getline(sess,e,',')){
                    if(e.size()==2&&e[0]=='[')
                    {
                        e = e.substr(1,1);
                        list_of_sessions.addBack(e);
                    }
                    else if(e.size()==2&&e[1]==']')
                    {
                        e = e.substr(0,1);
                        list_of_sessions.addBack(e);
                    }
                    else if(e.size()==3)
                    {
                        e = e.substr(1,1);
                        list_of_sessions.addBack(e);
                    }
                }
            }
            fitness_linked_list.addBack(Fitness(class_ID, class_name, list_of_sessions));
        }
    file.close(); // close the file
}


void load_session(string path) // load session file
{
    ifstream file(path);
    string line;
    getline(file, line); // skip the first unnecessary line
    string session_ID,class_ID,max_cap,session_date,session_time,room_number,member;

        while (getline(file, line)) 
        {
            stringstream ss(line);
            getline(ss, session_ID, ','); // take a variable/value one by one separated by comma
            getline(ss, class_ID, ',');
            getline(ss, max_cap, ',');
            getline(ss, session_date, ',');
            getline(ss, session_time, ',');
            getline(ss, room_number, ',');
            getline(ss, member,'\n');
            DoublyLinkedList list_of_registered_members; // registered members list inside the member list
            if(member.size()>2){
                stringstream mem(member);
                string e;
                while(getline(mem,e,',')){
                    if(e.size()==5&&e[0]=='['){

                        e = e.substr(1,4);
                        list_of_registered_members.addBack(e);
                    }
                    else if(e.size()==5&&e[4]==']')
                    {
                        e = e.substr(0,4);
                        list_of_registered_members.addBack(e);
                    }
                    else if(e.size()==6)
                    {
                        e = e.substr(1,4);
                        list_of_registered_members.addBack(e);
                    }
                }
            }
            session_linked_list.addBack(Session(session_ID, class_ID, max_cap, session_date, session_time,room_number, list_of_registered_members));
        }
    file.close(); // close the file
}



// DUMP DATA
//========================================================================================================================
void DumpMemberData() //Dump data to member txt file
{
    ofstream file("Members.txt"); // load file to dump data to
    file<<"member_ID,first_name,last_name,username,password,list_of_bookings"<<endl; // write the first line of file
    MemberNode* current = member_linked_list.head->next; 

    while(current->next!=NULL){ // loop thru memberlinkedlist to dump each member data
        file<<current->elem.member_ID<<","<<current->elem.first_name<<","<<current->elem.last_name<<","<<current->elem.username<<","<<current->elem.password<<",";

        Node* curr = current->elem.list_of_bookings.head->next;
        file<<"[";
        if(current->elem.list_of_bookings.empty()){
            file<<"]"<<endl;
        }
        else{
            while(curr!=current->elem.list_of_bookings.tail){
                if(curr==current->elem.list_of_bookings.tail->prev){
                    file<<curr->elem<<"]"<<endl;
                }
                else{
                    file<<curr->elem<<",";
                }
                curr = curr->next;
            }
        }
        current = current->next;
    }
}

void DumpFitnessData() //Dump data to fitness text file
{
    ofstream file("FitnessClasses.txt"); // load file to dump data to
    file<<"class_ID,class_name,list_of_sessions"<<endl; // write the first line of file
    FitnessNode* current = fitness_linked_list.head->next; 

    while(current->next!=NULL){ // loop thru fitnesslinkedlist to dump each member data
        file<<current->elem.class_ID<<","<<current->elem.class_name<<",";

        Node* curr = current->elem.list_of_sessions.head->next;
        file<<"[";
        if(current->elem.list_of_sessions.empty()){
            file<<"]"<<endl;
        }
        while(curr!=current->elem.list_of_sessions.tail){
            if(curr->next == current->elem.list_of_sessions.tail){
                file<<curr->elem<<"]"<<endl;
            }
            else{
                file<<curr->elem<<",";
            }
            curr = curr->next;
        }
        current = current->next;
    }
}

void DumpSessionData() //Dump data to session txt file
{
    ofstream file("Sessions.txt"); // load file to dump data to
    file<<"session_ID,class_ID,max_cap,session_date,session_time,room_number,list_of_registered_members"<<endl; // write the first line of file
    SessionNode* current = session_linked_list.head->next;

    while(current->next!=NULL){ // loop thru sessionlinkedlist to dump each member data
        file<<current->elem.session_ID<<","<<current->elem.class_ID<<","<<current->elem.max_cap<<","<<current->elem.session_date<<","<<current->elem.session_time<<","<<current->elem.room_number<<",";

        Node* curr = current->elem.list_of_registered_members.head->next;
        file<<"[";
        if(current->elem.list_of_registered_members.empty()){
            file<<"]"<<endl;
        }
        while(curr!=current->elem.list_of_registered_members.tail){
            if(curr->next == current->elem.list_of_registered_members.tail){
                file<<curr->elem<<"]"<<endl;
            }
            else{
                file<<curr->elem<<",";
            }
            curr = curr->next;
        }
        current = current->next;
    }
}





// FUNCTIONS TO BE CALLED BY USER'S CHOICES IN MENU
//========================================================================================================================
void MemberRegister() // a person registers as a new member
{
    MemberNode *current = member_linked_list.head;
    string first_name, last_name, username, password;
    int four_digits, member_ID;
    cout<<"Enter your first name: ";
    cin>>first_name;
    cout<<"Enter your last name: ";
    cin>>last_name;

    // make a new member ID and username
    while (current != NULL) // loop thru the end of the list
    {
        four_digits = rand()%9000 + 1000; // randomly generate four digits
        if ((current->elem.member_ID) != to_string(four_digits))
        {
            to_lowercase(first_name); // direct to function that converts to lowercase
            to_lowercase(last_name);
            username = first_name + to_string(four_digits); // create new username
            password = last_name + to_string(rand()%9000+1000); // create new password
            cout<<"Your username is: "<<username<<endl; 
            cout<<"Your password is: "<<password<<endl;
            
            ofstream file; // add information in the file 
            file.open("Members.txt", std::ios_base::app);
            file<<four_digits<<","<<first_name<<","<<last_name<<","<<username<<","<<password<<","<<"[]";
            file.close();
            break;
        }
        current = current->next;
    }
    load_members("Members.txt"); // load data again
    cout << "You are added sucessfully" << endl;
    cout<<endl;
}


void AdminRegisterMember() // admin registers a new member for a person
{
	MemberNode *current = member_linked_list.head;
	string first_name, last_name, username, password;

    // make a new member ID and username
	int four_digits, member_ID;
	cout<<"Enter a person's first name: "<<endl;
	cin>>first_name;
	cout<<"Enter a person's last name: "<<endl;
	cin>>last_name;

	// Make a new MemberID and Username
	while (current != NULL) // loop thru the end of the list
	{
		four_digits = rand()%9000+1000; // randomly generate four digits
		if ((current->elem.member_ID) != to_string(four_digits))
		{
            to_lowercase(first_name); // direct to function that converts to lowercase
            to_lowercase(last_name);
			username = first_name + to_string(four_digits); // create new username
			password = last_name + to_string(rand()%9000+1000); // create new password
            cout<<"His/her username is: "<<username<<endl;
            cout<<"His/her password is: "<<password<<endl;
            
            ofstream file; // add information in the file 
            file.open("Members.txt", std::ios_base::app);
            file<<four_digits<<","<<first_name<<","<<last_name<<","<<username<<","<<password<<","<<"[]";
            file.close();
			break;
		}
		current = current->next;
	}
    load_members("Members.txt"); // load data again
	cout << "The member is added sucessfully" << endl;
    cout<<endl;
}


void ViewListOfBookings() // member can see his/her current bookings
{
    MemberNode *current = member_linked_list.head->next;
    cout<<"This is your current bookings' session ID:"<<endl;
    
    while(current!=NULL){ // loop thru memberlinkedlist to find member that has the memberid with the current
        if(current->elem.member_ID == currentMember_ID){
            current->elem.list_of_bookings.display();
            cout<<endl;
        }
        current = current->next;
    }
    cout<<endl;
    
}


void AdminAddFitness() // admin adds a fitness class
{
    FitnessNode *current = fitness_linked_list.head->next;
	string class_ID,class_name;
	string session;

	cout<<"Enter a class ID: "<<endl;
    while(current != NULL){ // loop thru fitnesslinkedlist to find fitness that has the classid with the current
        cin>>class_ID;
        if(class_ID == current->elem.class_ID){
            current = current->next;
            cout<<"Enter different class ID: "<<endl; // enter a different ID to create a new one
        }
        else{
            break;
        }
    }

	cout<<"Enter a class name: "<<endl; // set the class name
	cin>>class_name;

	cout<<"Enter a list of sessions, separated by commas: "<<endl; // set lists of sessions
	cin>>session;
    DoublyLinkedList list_session;
    for(int i=0; i<session.size(); i++){
        char c = session[i];
        if(c!=','){
            string s(1,session[i]);
            list_session.addBack(s);
        }
    }

    DoublyLinkedList copyList; // copying the session data to a new linkedlist
   
    Node *c = list_session.head->next;
    while(c->next!=NULL){
        copyList.addBack(c->elem);
        c=c->next;
    }
    fitness_linked_list.addBack(Fitness(class_ID, class_name, copyList));
    
    ofstream file; // doucment the addition in the file 
    file.open("FitnessClasses.txt",std::ios_base::app);
    file<<endl<<class_ID<<","<<class_name<<","<<"["; // in this format
    
    Node* curr = copyList.head->next;
    while(curr!=copyList.tail){
        if(curr->next == copyList.tail){
            file<<curr->elem<<"]"<<endl;
        }
        else{
            file<<curr->elem<<",";
        }
        curr = curr->next;
    }
    file.close(); // close the file 
	cout << "The fitness class is added sucessfully" << endl;
    cout<<endl;
}



void AdminDeleteFitness() // admin delete a fitness class
{
	string class_ID;
	FitnessNode *current= fitness_linked_list.head;
	cout<<"Enter a class ID to delete: "<<endl; 
	cin>>class_ID;

	while (current->next != NULL) // if the fitness is existent: 
	{		
		if (current->elem.class_ID == class_ID)
		{
            FitnessNode* before = current->prev;
            FitnessNode* after = current->next;
            
            current->prev->next = after;
            current->next->prev = before;
            
			delete current; // if found, delete
		}
		current = current->next;
	}
    
    SessionNode *c = session_linked_list.head; // loop thru sessionlinkedlist to delete the session witht the specified class ID
    while(c->next != session_linked_list.tail){
        if(c->elem.class_ID == class_ID){
            SessionNode* before = c->prev;
            SessionNode* after = c->next;
            
            c->prev->next = after;
            c->next->prev = before;
            delete c;
        }
        c = c->next;
    }
    DumpFitnessData(); //Dump the changed fitness data to the txt file
	cout<< "The fitness class has been deleted successfully"<<endl;
    cout<<endl;
}



void AdminUpdateFitnessName() // admin updates a session's name
{
	string class_ID,class_name, new_class_name;
    FitnessNode *current = fitness_linked_list.head->next;
	cout<<"Enter a fitness class ID to update: "<<endl;
	cin>>class_ID;
	while (current->next != NULL) // look thru the end of the list
	{
		if (((current->elem).get_class_ID()) == class_ID)
		{
			cout<<"Enter the updated fitness class name: "<<endl; // change the name of the fitness class
			cin>>new_class_name;
            (current->elem).class_name = new_class_name;
		}
		current = current->next;
	}
    DumpFitnessData(); //Dump the changed fitness data to the txt file.
	cout<< "The name of a fitness class has been updated successfully"<<endl;
    cout<<endl;
}



void AdminAddSession() // admin add a session for a fitness class
{
	string class_ID,class_name,max_cap,session_date,session_time,room_number,session_ID;
	FitnessNode *current = fitness_linked_list.head->next;

	// get information for the addition of a session
	cout<<"Enter the fitness class ID to add a session to: "<<endl;
	cin>> class_ID;
	cout<<"Enter new session ID to add: "<<endl;
	cin>>session_ID;
    cout<<"Enter maximum capacity (default = 20): "<<endl;
    cin>>max_cap;
    cout<<"Enter Session Date in DD-MM-YR format: "<<endl;
    cin>>session_date;
    cout<<"Enter Session Time in 16:00 format: "<<endl;
    cin>>session_time;
    cout<<"Enter room number: "<<endl;
    cin>>room_number;
    
    while(current->next !=NULL){ // loop thru the end of the list
        if(current->elem.get_class_ID() == class_ID){
            current->elem.list_of_sessions.addBack(session_ID);
        }
        current = current->next;
    }

    DoublyLinkedList emptyList = DoublyLinkedList();
    
    // creating a new session object and appending it back to the sessionlinkedlist
    session_linked_list.addBack(Session(session_ID,class_ID,max_cap,session_date,session_time,room_number,emptyList));
    DumpFitnessData(); //Dump the changed fitness data to fitness txt file
    DumpSessionData(); //Dump the changed session data to the session txt file
    cout<< "The session has been added successfully"<<endl;
    cout<<endl;
}



void AdminUpdateSession() // admin updates session details
{
	string session_ID,max_cap,session_date,session_time,room_number;
	SessionNode *current = session_linked_list.head->next;
	cout<<"Enter a Session ID to update: "<<endl;
	cin>>session_ID;
	while (current->next != NULL)
	{
		if (current->elem.get_session_ID() == session_ID)
		{
			// print the current information on session details
            cout<< current->elem.get_session_ID();
            cout<<" currently has "<<endl;
            cout<<"Max Capacity: "<< current->elem.get_max_cap()<<endl;
            cout<<"Session Date: "<< current->elem.get_session_date()<<endl;
            cout<<"Session Time: "<< current->elem.get_session_time()<<endl;
            cout<<"Room Number: "<< current->elem.get_room_number()<<endl;
            cout<<endl;

            // update the information
			cout<< "Enter the updated Max Capacity: "<<endl;
			cin>> current->elem.max_cap;
			cout<< "Enter the updated Session Date in this format 06-16-21 : "<<endl;
			cin>> current->elem.session_date;
			cout<< "Enter the updated Session Time in this format 16:00 : "<<endl;
			cin>> current->elem.session_time;
			cout<< "Enter the updated Room Number: "<<endl;
			cin>> current->elem.room_number;
			cout<< "Details of a Session has been updated successfully"<<endl;
		}
        current = current->next;
	}
    DumpSessionData(); //Dump the changed session data to the session txt file
    cout<< "The session information has been updated successfully"<<endl;
    cout<<endl;
}


void AdminDeleteSession() // admin delete a session
{
    string session_ID;
    SessionNode *current= session_linked_list.head;
    cout<<"Enter a session ID to delete: "<<endl;
    cin>>session_ID;

    while (current->next != NULL) // look thru the end of the list
    {
        if (current->elem.session_ID == session_ID) //deleting the session that has the same session id as specified
        {
            SessionNode* before = current->prev;
            SessionNode* after = current->next;
            
            current->prev->next = after;
            current->next->prev = before;
            
            current->elem.list_of_registered_members.~DoublyLinkedList();
            delete current;
        }
        current = current->next;
    }
    DumpSessionData(); //dump the new session data to the txt file

    // dump the session from the list of fitness classes

    cout<< "The session has been deleted successfully"<<endl;
    cout<<endl;
}


void AdminViewSession() // admin view session details
{
    string session_ID;
    SessionNode* current = session_linked_list.head->next;
    cout<<"Enter a session ID that you wish to view details for: ";
    cin>>session_ID;
    while (current->next != NULL) // loop thru the end of the list
    {
        if (current->elem.get_session_ID() == session_ID) //print out the session data if the session id is same as the specified session id
        {
            cout<< "Session ID is "<<current->elem.get_session_ID()<<endl;
            cout<< "Maximum Capacity is "<<current->elem.get_max_cap()<<endl;
            cout<< "Session Date is "<<current->elem.get_session_date()<<endl;
            cout<< "Session Time is "<<current->elem.get_session_time()<<endl;
            cout<< "Room Number is "<<current->elem.get_room_number()<<endl;
        }
        current = current->next;
    }
    cout<<endl;
}


void AdminViewSessionMemberList() // admin view the list of members in a session
{
    string session_ID;
    SessionNode* current = session_linked_list.head->next;
    cout<<"Enter a session ID that you wish to view the members of: "<<endl;
    cin>>session_ID;
    cout<<endl;

    while(current->next != NULL){ // loop thru the end of the list
        if(current->elem.get_session_ID() == session_ID){ //display the list of registerd members if the session id is the same as the specified session id
            current->elem.list_of_registered_members.display();
        }
        current = current->next;
    }
    cout<<endl;
}


// void AdminViewSortedSessionList() // admin view the list of members sorted by last names in a session
// {
    
//     string session_ID;

//     SessionNode* current = session_linked_list.head->next;
//     cout<<"Enter a session ID that you wish to view the Members of: ";
//     cin>>session_ID;

//     while(current->next != NULL){ // loop thru the end of the list
//         if(current->elem.get_session_ID() == session_ID){ // view the list of registered members if the session id is the same as the specified session id
//         	Node *curr = new Node();
//         	MemberNode *c = member_linked_list.head;
//         	DoublyLinkedList members = new DoublyLinkedList();

//         	while(curr->next != current->elem.list_of_registered_members.tail){
//         		members.addBack(curr.elem);
//         		curr = curr->next;
//         	}

//         	Node *a = members.head;


//         	while(c->next != member_linked_list.tail){
//         		if(c->elem.last_name == a->elem){

//         		}
//         	}

//             current->elem.list_of_registered_members.display();
//         }
//         current = current->next;
//     }
//     cout<<endl;
// }



void AdminAMemberBookings() // admin view the list of bookings a member have
{
    string member_ID;
    MemberNode* current = member_linked_list.head->next;
    cout<<"Enter a member ID that you wish to view bookings for: "<<endl;
    cin>>member_ID;

    while(current->next != NULL) // loop thru the end of the lsit
    {
        if(current->elem.member_ID == member_ID) //displaying the list of bookings if the member id is the same as the specified member id
        {
            current->elem.list_of_bookings.display();
        }
        current = current->next;
    }
    cout<<endl;
}


void ViewAvailableSessions() // admin and member can view the list of sessions for a certain fitness that are available
{   
    cout<<"Enter fitness class ID to view sessions: "<<endl;
    string class_ID;
    cin>>class_ID;
    FitnessNode *current = fitness_linked_list.head;
    int cnt1=0;
    int cnt2=0;
    while(current!=NULL){ // loop thru the end of the  fitness list
        if(current->elem.class_ID == class_ID){
            SessionNode* curr = session_linked_list.head;
            cnt2++;
            while(curr != NULL){ // loop through the session list of the found session from the previous loop
                if(curr->elem.class_ID == class_ID){ 
                    if(curr->elem.list_of_registered_members.size() < stoi(curr->elem.max_cap)){   // check if the size of the registered member list <= max capacity of the session
                        cout<<"Session ID: "<<curr->elem.session_ID<<endl;
                        cout<<"Maximum Capacity: "<<curr->elem.max_cap<<endl;
                        cout<<"Session Date: "<<curr->elem.session_date<<endl;
                        cout<<"Session Time: "<<curr->elem.session_time<<endl;
                        cout<<"Room Number: "<<curr->elem.room_number<<endl;
                        cnt1++;

                        cout<<"Current session size: "<<(curr->elem.list_of_registered_members.size() - 1)<<endl;
                    }           
                }
                curr = curr->next;
            }
        }
        current = current->next;
    }
    
    if(cnt2!=0&&cnt1==0){
        cout<<"No Available Sessions!"<<endl;
    }
    if(cnt2==0){
        cout<<"Class ID Not Found!"<<endl;
    }
    cout<<endl;
}

// void AdminViewMemberCommon()
// {
// 	MemberNode *current1 = member_linked_list.head->next;
// 	MemberNode *current2 = member_linked_list.head->next;

// 	MemberLinkedList list_common = MemberLinkedList();

// 	int cnt = 0;

// 	while(current1->next != member_linked_list.tail){
// 		Node *sessNode = new Node();
// 		if(current1.elem.list_of_sessions.)
// 	}

// }



void MemberBookSession() // member book a session
{
    string class_ID, session_ID;
    cout<<"Enter a Fitness Class ID you would like to book: "<<endl;
    cin>>class_ID;
    cout<<"Available Sessions: "<<endl; 
    int cnt1 = 0;
    int cnt2 = 0;
    
    FitnessNode *current = fitness_linked_list.head;
    while(current!=NULL) // loop thru the end of the fitness list
    {
        if(current->elem.class_ID == class_ID)
        {
            SessionNode* curr = session_linked_list.head;
            cnt2++;
            while(curr != NULL) // loop thru the end of the session list
            {
                if(curr->elem.class_ID == class_ID)
                {
                    if(curr->elem.list_of_registered_members.size() < stoi(curr->elem.max_cap)) // check if the size of the registered member list <= max capacity of the session
                    {
                        cout<<"Session ID: "<<curr->elem.session_ID<<endl;
                        cout<<"Maximum Capacity: "<<curr->elem.max_cap<<endl;
                        cout<<"Session Date: "<<curr->elem.session_date<<endl;
                        cout<<"Session Time: "<<curr->elem.session_time<<endl;
                        cout<<"Room Number: "<<curr->elem.room_number<<endl;
                        cout<<endl;
                        cnt1++;
//                        cout<<"Current session size: "<<curr->elem.list_of_registered_members.size()<<endl;
                    }
                    else
                    	cout<<"The Class is Full!"<<endl;
                }
                curr = curr->next;
            }
        }
        current = current->next;
    }

    if(cnt2!=0&&cnt1==0){ // error filtering
        cout<<"No Available Sessions!"<<endl;
    }
    if(cnt2==0){ // error filtering
        cout<<"Class ID Not Found!"<<endl;
    }
    
    if(cnt2!=0&&cnt1!=0){
        cout<<"Enter the session ID that you want to book: "<<endl;
        cin>>session_ID;
    }
    
    SessionNode* curr = session_linked_list.head; // appending current member ID to the list of registered members of the session
    while(curr!=NULL){
        if(curr->elem.session_ID == session_ID){
            curr->elem.list_of_registered_members.addBack(currentMember_ID);
            }
        curr = curr->next;
        }

    MemberNode *member = member_linked_list.head->next; // appedning the session ID to the list of bookings of current member
    while(member!=NULL){
        if(member->elem.member_ID == currentMember_ID){
            member->elem.list_of_bookings.addBack(session_ID);
        }
        member = member->next;
    }
    DumpMemberData();
    cout<< "The session has been booked successfully"<<endl;
    cout<<endl;
}


void MemberCancelBooking() // member cancel booking
{
    string session_ID;
    ViewListOfBookings();
    cout<<"Enter Session ID that you want to cancel: "<<endl;
    cin>>session_ID;
    
    MemberNode* current = member_linked_list.head;
    while(current!=NULL){ // look thru the end of the member list
        if(current->elem.list_of_bookings.checkElem(session_ID)){
            Node* curr;
            curr = current->elem.list_of_bookings.head;
            while(curr!=NULL){  // look thru the end of the list_of_bookings list
                if(curr->elem == session_ID){ //deleting the session if the session with the specified session id exists
                    if(curr->prev == current->elem.list_of_bookings.head){
                        current->elem.list_of_bookings.removeFront();
                    }
                    else if(curr->next == current->elem.list_of_bookings.tail){
                        current->elem.list_of_bookings.removeBack();
                    }
                    else{
                        Node* tmp = curr;
                        curr->next->prev = tmp->prev;
                        curr->prev->next = tmp->next;
                        delete curr;
                    }
                }
                curr = curr->next;
            }
        }
        current = current->next;
    }
    cout<< "The session has been canceled successfully"<<endl;
    cout<<endl;
}





// DIRECTORY for ADMIN & MEMBERS
//========================================================================================================================
int Quit() // whenever Quit is called, exit the program
{
    return EXIT_SUCCESS;
}

void AdminLoggedInMenu() // if admin logged in, give more options
{
    int adminchoice;
    cout<<"1 Register as a new member"<<endl;
    cout<<"2 Add a fitness class"<<endl;
    cout<<"3 Delete a fitness class"<<endl;
    cout<<"4 Change a fitness class name"<<endl;
    cout<<"5 Add a session"<<endl;
    cout<<"6 Update a session's details"<<endl;
    cout<<"7 Delete a session"<<endl;
    cout<<"8 View a session's details"<<endl;
    cout<<"9 View a list of members in a session"<<endl;
    cout<<"10 View a sorted-list of Members in a session by their last names"<<endl;
    cout<<"11 View the list of bookings a member booked"<<endl;
    cout<<"12 View the list of available sessions for fitness classes"<<endl;
	cout<<"13 View the list of members having multiple common classes"<<endl;
    cout<<"14 Quit program"<<endl;
    cin>>adminchoice;
    
    if (adminchoice == 1){
        AdminRegisterMember();
    }
    if (adminchoice == 2){
        AdminAddFitness();
    }
    if (adminchoice == 3){
        AdminDeleteFitness();
    }
    if (adminchoice == 4){
        AdminUpdateFitnessName();
    }
    if (adminchoice == 5){
        AdminAddSession();
    }
    if (adminchoice == 6){
        AdminUpdateSession();
    }
    if (adminchoice == 7){
        AdminDeleteSession();
    }
    if (adminchoice == 8){
        AdminViewSession();
    }
    if (adminchoice == 9){
        AdminViewSessionMemberList();
    }
    // if (adminchoice == 10){
    //     AdminViewSortedSessionList();
    // }
    if (adminchoice == 11){
        AdminAMemberBookings();
    }
    if (adminchoice == 12){
        ViewAvailableSessions();
    }
    // if (adminchoice == 13){
  		// AdminViewMemberCommon();
    // } 
    if (adminchoice == 14){
        Quit();
    }
}


void MemberLoggedInMenu() // if member logged in, give more options
{
    int memberchoice;
    cout<<endl;
    cout<<"1 View the list of available sessions for fitness classes"<<endl;
    cout<<"2 Book a session"<<endl;
    cout<<"3 Cancel a booking"<<endl;
    cout<<"4 View current bookings"<<endl;
    cout<<"5 Quit program"<<endl;
    cout<<"Enter a number from above to continue: "<<endl;
    
    cin>>memberchoice;
    if (memberchoice == 1){
        ViewAvailableSessions();
    }
    if (memberchoice == 2){
        MemberBookSession();
    }
    if (memberchoice == 3){
        MemberCancelBooking();
    }
    if (memberchoice ==4){
        ViewListOfBookings();
    }
    if (memberchoice == 5){
        Quit();
    }
}


bool AdminLogin() // check admin's login information
{
	AdminNode *current= admin_linked_list.head;
	string input_username, input_password;
	cout<<"Enter your username: "<<endl;
	cin>>input_username;
	cout<<"Enter your password: "<<endl;
	cin>>input_password;
    while(current!=NULL) // move along the node to check if username and password both exist
    { 
        if ((current->elem.username == input_username) && (current->elem.password == input_password)) // check if both are correct
        { // check if both are correct
            cout<<endl;
            cout<<input_username<<", welcome back!"<<endl;
            cout<<"-------------------------------------------"<<endl;
            currentAdmin_ID = current->elem.admin_ID;
            return true;
            }
        else
			current = current->next;
    }
    return false;
}


bool MemberLogin() // check member's login information
{
	MemberNode *current=member_linked_list.head;

	string input_username, input_password;
	cout<<"Enter your username: "<<endl;
	cin>>input_username;
	cout<<"Enter your password: "<<endl;
	cin>>input_password;

	while (current!=NULL) // move along the node to check if username and password both exist
	{
        if((current->elem.username == input_username) && (current->elem.password == input_password)) // check if both are correct
        {
            cout<<endl;
			cout<<input_username<<", welcome back!"<<endl;
            cout<<"-------------------------------------------"<<endl;
            currentMember_ID = current->elem.member_ID;
            return true;
        }
		else
			current = current->next;
	}
    return false;
}


void Login1() // function to check if member is logged in to proceed to loggedinmenu
{
    if(MemberLogin()==true){
        MemberLoggedInMenu();
    }
    else{
        cout<<"Wrong Credentials!"<<endl; // print if wrong input
    }
}

void Login2() // function to check if admin is logged in to proceed to loggedinmenu
{
    if(AdminLogin()==true){
        AdminLoggedInMenu();
    }
    else{
        cout<<"Wrong Credentials!"<<endl; // print if wrong input
    }
}



// MAIN FUNCTION
//========================================================================================================================
bool endProgram = false;
int main()
{
    srand(time(0)); //For random number assingmnet for registering members
	load_admin("Admins.txt"); // call all the files needed
	load_members("Members.txt");
    DumpMemberData();
	load_fitness("FitnessClasses.txt");
	load_session("Sessions.txt");
    
    while(!endProgram) // if not end, call settings below
    {
            int userchoice;
            cout<<"-------------------------------------------"<<endl;
            cout<<"Welcome to Data Structures Fitness Center"<<endl;
            cout<<"-------------------------------------------"<<endl;
            cout<<"1 Member Login"<<endl;
            cout<<"2 Admin Login"<<endl;
            cout<<"3 New Member Register"<<endl;
            cout<<"4 Quit"<<endl;
            cout<<"Enter a number from above to continue: "<<endl;
       
            while (!(cin>>userchoice))
            {
            	cout<< "Try Again! "<<endl;
            	cin.clear();
            	cin.ignore(5,'\n');
            }
                if (userchoice == 1){
                    Login1();
                }
                if (userchoice == 2){
                    Login2();
                }
                if (userchoice == 3){
                    MemberRegister();
                }
                if (userchoice == 4){
                    return 0;
                }
        }
    return 0;
}




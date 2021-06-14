#include <iostream>
#include <vector>
#include <list>
#include <iterator>

using namespace std;

enum Sex {
    Male,
    Female,
    None
};

class Object {
public:
    int ID;
    int VALUE;
    string objType;
    Sex sex;
};

class Person {
private:
    Sex sex;
};

class Car : public Object {
public:
    //constructor for Car
    Car(int ID) {
        Object::ID = ID;
        Object::VALUE = this->VALUE;
        Object::objType = this->objType;
        Object::sex = None;
    }

    /**
     * getters for id
     * may be very useful for further work with this code
     * @return
     */
    int getId() {
        return ID;
    }

    /**
     * setter for id
     * may be very useful for further work with this code
     * @param id
     */
    void setId(int id) {
        ID = id;
    }

    /**
     * getters for value
     * no setter for value because it should be unchangeable
     * @return
     */
    int getValue() {
        return VALUE;
    }

private:
    string objType = "I am a car";
    int ID;
    static constexpr int VALUE = 1000;
};

class Student : public Object, public Person {
public:
    //constructor for Students
    Student(int ID) {
        Object::ID = ID;
        Object::VALUE = this->VALUE;
        Object::objType = this->objType;
    }


    //another constructor
    Student(int ID, Sex sex) {
        Object::ID = ID;
        if (sex == Male) {
            Object::VALUE = this->VALUE + 10;
            Object::objType = this->objType + " Male";
            Object::sex = Male;
        } else {
            Object::VALUE = this->VALUE;
            Object::objType = this->objType + " Female";
            Object::sex = Female;
        }
        this->sex = sex;
    }

    /**
     * getters for id
     * may be very useful for further work with this code
     * @return
     */
    int getId() {
        return ID;
    }

    /**
     * setter for id
     * may be very useful for further work with this code
     * @param id
     */
    void setId(int id) {
        ID = id;
    }

    /**
     * getters for value
     * no setter for value because it should be unchangeable
     * @return
     */
    int getValue() const {
        return VALUE;
    }

private:
    Sex sex;
    string objType = "I am a student";
    int ID;
    int VALUE = 10;

};

class Transformer : public Object, public Person {
public:
    //constructor for Transformers
    Transformer(int ID) {
        Object::ID = ID;
        Object::VALUE = this->VALUE;
        Object::objType = this->objType;
    }

    //another constructor
    Transformer(int ID, Sex sex) {
        Object::ID = ID;

        if (sex == Male) {
            Object::VALUE = this->VALUE + 10;
            Object::objType = this->objType + " Male";
            Object::sex = Male;
        } else {
            Object::VALUE = this->VALUE;
            Object::objType = this->objType + " Female";
            Object::sex=Female;
        }
        this->sex = sex;
    }

    /**
    * getters for id
    * may be very useful for further work with this code
    * @return
    */
    int getId() {
        return ID;
    }

    /**
    * setter for id
    * may be very useful for further work with this code
    * @param id
    */
    void setId(int id) {
        ID = id;
    }

    /**
     * getters for value
     * no setter for value because it should be unchangeable
     * @return
     */
    int getValue1() const {
        return VALUE;
    }

private:
    string objType = "I am transformer";
    Sex sex;
    int ID;
    int VALUE = 100;
};

class StackAdaptor {//ITEM 2.2: stack adaptor
public:
    vector<Object> stack;

    //standard push method, but I called it the same as for vectors to make other methods general
    void push_back(Object obj) {
        stack.push_back(obj);
    }

    //standard pop method, deletes the last item in stack
    void pop() {
        stack.erase(stack.end() - 1);
    }

    //standard method, returns teh size
    int size() {
        return stack.size();
    }

    //I declared here begin() iterator from vector, due to I may use it other generalized methods
    const __wrap_iter<vector<Object, allocator<Object>>::const_pointer> begin() const {
        return stack.begin();
    };

    //I declared here end() iterator from vector, due to I may use it other generalized methods
    const __wrap_iter<vector<Object, allocator<Object>>::const_pointer> end() const {
        return stack.end();
    };

};

//displays all the item for a given container, by iterating through the whole container
template<typename C>
void display(const C &container) {//ITEM 5: function which shows the elements in container
    for (const auto &e : container) {
        cout << "ID:" << e.ID << "   " << e.objType << endl;
    }
}

//shuffles by reversing it, works for eny type of required container, returns reversed container
template<class T>
T doScramble(T vec) {//ITEM 3: shuffles by reversing it, works for eny type of required container
    T reversed;
    for (int i = 0; i < vec.size(); ++i) {
        reversed.push_back(*(vec.begin() + vec.size() - 1 - i));//ITEM 3.f: function uses the iterator to add elements in new container
    }
    return reversed;
}

template<class T>
T sort(T vec) {//ITEM 4: sorting
    //insertion sort
    int key;
    for (int i = 1; i < vec.size(); ++i) {
        key = vec[i].ID;
        int j = i - 1;
        while (j >= 0 && vec[j].ID > key) {
            vec[j + 1].ID = vec[j].ID;
            j = j - 1;
        }
        vec[j + 1].ID = key;
    }
    return vec;
}

template<>//sorting by insertion
vector<Object> sort(vector<Object> vec) {//ITEM 3.d: explicit specialization for vector
    //insertion sort
    int key;
    for (int i = 1; i < vec.size(); ++i) {
        key = vec[i].ID;
        int j = i - 1;
        while (j >= 0 && vec[j].ID > key) {
            vec[j + 1].ID = vec[j].ID;
            j = j - 1;
        }
        vec[j + 1].ID = key;
    }
    return vec;
}

//function which shows the elements in container
template<typename C>
void showLow(const C &container) {//ITEM 5: function which shows the elements in container
    const auto &e = *container.begin();
    cout << "ID:" << e.ID << "   " << e.objType << endl;
}

// bool function to determine whether it is a men or a women or a car(None)
bool isMale(Object obj) { //ITEM 7: bool function to determine whether it is a men or a women or a car(None)
    if (obj.sex == Male) {
        return true;
    }else{
        return false;
    }
}

//shows only men in containers
template<typename C>
void showMale(const C &container) {//ITEM 7: shows only men in containers
    for (const auto &e : container) {
        if(isMale(e)) {//ITEM 3.g: usage of predicate function
            cout << "ID:" << e.ID << "   " << e.objType << endl;
        }
    }
}

vector<Object> things;//ITEM 1: creating vector and adding things to it
list<Object> list_things; //ITEM 2.1: list with copies ov things
StackAdaptor stack; //ITEM 2.2: stack

//insertion elements automatically, user enters amount of things and the method automatically generate things and adds it to stack, vector, list
template<typename T, int n>//ITEM 3.b: inserting with non-type parameter
void inserting(){
    for (int i = 0; i <= n/3; ++i) {
        Object *t1 = new Car(i + 1);//ITEM 1: creating vector and adding things to it
        decltype(new Car(i + 1)) t2 = new Car(i + 1); //ITEM 3.e: usage of decltype to create things
        things.push_back(*t2);
        list_things.push_back(*t2);
        stack.push_back(*t2);
    }
    for (int i = n/3+1; i <= 2*n/3; ++i) {
        if (i % 2 == 0) {
            Object *t1 = new Transformer(i + 1, Female);//ITEM 1: creating vector and adding things to it
            things.push_back(*t1);
            list_things.push_back(*t1);
            stack.push_back(*t1);
        } else {
            Object *t1 = new Transformer(i + 1, Male);//ITEM 1: creating vector and adding things to it
            things.push_back(*t1);
            list_things.push_back(*t1);
            stack.push_back(*t1);
        }
    }
    for (int i = 2*n/3 +1; i < n; ++i) {
        if (i % 2 == 0) {
            Object *t1 = new Student(i + 1, Female);//ITEM 1: creating vector and adding things to it
            things.push_back(*t1);
            list_things.push_back(*t1);
            stack.push_back(*t1);
        } else {
            Object *t1 = new Student(i + 1, Male);//ITEM 1: creating vector and adding things to it
            things.push_back(*t1);
            list_things.push_back(*t1);
            stack.push_back(*t1);
        }
    }
}


int main() {
    cout << "We have 25 boxes" << endl;
    inserting<Object, 25>();

    display(stack);//ITEM 3.c here it is called for stack
    cout<<endl;

    cout << "SHUFFLE" << endl;
    things = doScramble(things); //scrambling the items (in reverse order for example)
    display(things);//ITEM 3.c here it is called for vector

    cout << endl;

    cout << "Sorted by Insertion Sort" << endl;

    things = sort(things);
    display(things);

    cout<<endl;

    cout << "The lowest element in containers" << endl;
    showLow(stack);//ITEM 6: the lowest element, I used stack here to show that the method works for any container
    cout<<endl;

    cout << "The Gentlemen" << endl;
    showMale(things);

    return 0;
}


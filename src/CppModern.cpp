//============================================================================
// Name        : CppModern.cpp
// Author      : Randy Mujica
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <memory>
#include <string>

using namespace std;

// Defining your own initializer_list constructor
class MyVector {
	vector<int> m_vec;
public:
	MyVector(const initializer_list<int>& v)
	{
		for (auto item : v)
			m_vec.push_back(item);
	}

	vector<int> getNumbers(){
		return m_vec;
	}
};

int main() {

	//1. Initializer list: All containers support the initializer_list constructor
	vector<int> numbers = {1, 2, 3, 4, 5}; //Calling initializer list constructor
	for(auto n : numbers)
		cout << n << endl;

	MyVector my_vec = {1, 2, 3, 4};
	for (auto item : my_vec.getNumbers())
		cout << item << ' ';

	/* 2. Uniform initialization search order:
	 *  1. Initializer_list constructor
	 *	2. Regular constructor that take the appropriated parameter
	 *	3. Aggregate initializer: When the members are public
	 */
	class dog {
	public:
		int age;							  //3rd  choice

		dog(int a){							  // 2nd choice
			age = a;
		}

		dog(const initializer_list<int>& v){  // 1st choice
			age = *(v.begin());
		}

	};

	/*
	 * 3. Auto type
	 */

	/*
	 * 4. foreach
	 */
	for (auto item: numbers)    //works on any class that has begin() and end()
		cout << item << endl;   //readonly access

	for (auto& item: numbers){  //auto& for change the value of item
		item += 1;
		cout << item << endl;
	}

	/*
	 * 5. nullptr  :  nullptr and NULL are different
	 */

	/*
	 * 6. Enum class
	 */
	enum class apple {appleBig, appleGreen};
	enum class orange {orange1, orange2};
	apple a = apple::appleBig;
	orange o = orange::orange1;

	// You CANNOT compare apple with orange
	//	if (a == o) {
	//		cout << "The apple and orange are the same" << endl;
	//	}

	/*
	 * 7. static_assert
	 */
	// static_assert(sizeof(int) == 4);

	/*
	 * 8. Delegating constructor
	 */
	class cat {
		int age = 9; //member initialization allowed
		cat(){cout << "default constructor called" <<endl;}
		//default constructor can be called from custom
		cat(int a) : cat() {cout << "custom constructor called" << a <<endl;}
	};

	/*
	 * 9. Override (for virtual functions)
	 */

	class tv {
		virtual void A(int);
		virtual void B() const;
	public:
		virtual ~tv(){}
	};

	class BlackTv : public tv {
		virtual void A(int) override;  	  //It's mandatory putting the override word
		virtual void B() const override;  //It's mandatory putting the override word
	};

	/*
	 * 10. final : for virtual functions and for classes
	 */
	class key final { 					//no class can be derived from key
		virtual void press() final;		//no class can override press()
	public:
		virtual ~key(){}
	};

	/*
	 * 11. Compiler generated Default constructor
	 */
	class disk {
	public:
		disk(int size){}
	};

	//disk d; //Error: compiler will not generate default constructor
	//C++11
	class disk2 {
		public:
			disk2(int size){}
			disk2() = default;  //Force the compiler to generate the default constructor
		};

	disk2 d; //OK

	/*
	 * 12. delete
	 */
	class finger {
	public:
		finger(int size){}
		finger(double) = delete;					//delete finger(double) constructor
		finger& operator=(const finger&) = delete;	// delete the assignment operator
	};

	/*
	 * 13. constexpr : Force the computation to happen at compile time
	 */
//	constexpr int cube(int x) {return x*x*x;}
//	int value = cube(1289); //Computed at compile time

	/*
	 * 14. New string literals
	 */
	char* aa = u8"string"; 		//UTF8 string
	char16_t* bb = u"string"; 	//UTF16 string
	char32_t* cc = U"string"; 	//UTF32 string
	//char* dd = R"string"; 	//Raw string   DONOT WORK!

	/*
	 * 15. Lambda functions
	 */
	int c = 2;
	auto lambda = [&](int a, int b){return a+b+c; };  //& for accessing local variables
	cout << endl << lambda(1,2) <<endl;

	/*
	 * 16. Rvalue reference:
	 * 	- Moving semantics
	 * 	- Perfect forwarding
	 */

//	void printInt(int& a){cout << "lvalue reference" << a <<endl;}
//	void printInt(int&& a){cout << "rvalue reference" << a <<endl;}
//
//	int a = 5;
//
//	printInt(a); // call printInt(int&);
//	printInt(6); // call printInt(int&&);
//
//
//
//	class phone {
//		int size;
//		int* numbers; // A big array
//	public:
//		phone(const phone& p) {    //copy constructor
//			size = p.size;
//			numbers = new int[size];
//			for (int i=0; i<size; i++) {numbers[i] = p.numbers[i];}  // Deep copy =>> VERY HIGH COST
//		}
//		phone(phone&& p) {  //move constructor
//			size = p.size;
//			numbers = p.numbers;
//			p.numbers = nullptr;
//		}
//	};
//
//	void use(phone p);
//
//	phone ph;
//	use_by_ref(ph);         // called no constructor
//	use(ph);				// called copy constructor
//	use(phone());   		// called move constructor
//	use(std::move(ph)); 	//it will call the move constructor

	/*
	 * 17. Shared pointers: Smart pointers with reference counting
	 */

	class book {
		string title;
	public:
		book(string p_title): title(p_title){cout << "Book " << p_title <<" is created";}
		book() : title("nameless")  {cout << "Book nameless is created";}
		~book(){cout << "Book" << title << "is destroyed";}
		void bark(){cout << "Book " << title << "rules!" << endl;}
	};

	shared_ptr<book> p(new book("Cpp Modern")); //Count = 1
	{
		shared_ptr<book> p2 = p; //Count = 2
		p2->bark();
	}
	// Count = 1
	p->bark();
	// Count = 0

	shared_ptr<book> bo = make_shared<book>("Shared pointers book"); //faster and safer way to create a smart pointer


	return 0;
}

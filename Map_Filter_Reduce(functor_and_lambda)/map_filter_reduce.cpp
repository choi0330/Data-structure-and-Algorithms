#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

// the following templated functions are service functions to be used in the main 
// function below. Do not modify them.

// read in a vector -- do not modify
template <typename T>
std::vector<T> read() {
	std::vector<T> v;
	for (T x; std::cin >> x;)
		v.push_back(x);
	return v;
}

// apply a function to each element of v and return the modified v -- do not modify
template <typename T, typename F>
T  map(T v, F f) {
	for (auto & x : v)
		x = f(x);
	return v;
}

// apply a function to each element of v but return the old v -- do not modify
template <typename T, typename F>
T foreach(T t, F f) {
	for (auto x : t)
		f(x);
	return t;
}

// remove all elements from v that do not satisfy f(v) -- do not modify
template <typename T, typename F>
T filter(T v, F f) {
	v.erase(
		std::remove_if(std::begin(v), std::end(v), [&](auto x) {return !f(x); }),
		std::end(v)
	);
	return v;
}

// starting with r = init, 
// iteratively apply f(r,x) to r and each element x of v
// example reduce(vector, [](auto x, auto y){return x+y;}) returns the sum of all elements
template <typename T, typename F, typename R>
R reduce(T v, F f, R init) {
	auto r = init;
	for (auto x : v)
		r = f(r, x);
	return r;
}

// simple example data set
struct Student {
	std::string name;
	int xp;
	int semester;
};

// read a data-set
std::istream& operator>> (std::istream& in, Student& s) {
	return in >> s.name >> s.semester >> s.xp;
}

// write a data-set
std::ostream& operator<< (std::ostream& out, Student& s) {
	return out << "name = " << s.name
		<< " semester = " << s.semester
		<< " xp = " << s.xp;
}

int main() {
	int xp;
	std::cin >> xp; // read in minimal required experience points

	//auto students = read<Student>(); // read in student data

	// complete the following such that the list of students contains
	// all students with at least "xp" points where the semester count is
	// increased by one.
	// use filter / map using lambda expressions.
	// Once you have reached the goal
	// you can try to do everything in a single statement 
	// (using (parts of) the template functions map, reduce, foreach, read and reduce from above)
	// [even including reading and writing the result, if you dare]
	
	//// First
	//students = filter(students, [&](Student& student) ->bool {return student.xp >= xp; });
	//students = map(students, [&](Student& student)->Student { student.semester += 1; return student; });

	//// Second
	//students = map(filter(students, [&](Student& student) ->bool {return student.xp >= xp; }),
	//	[&](Student& student)->Student { student.semester += 1; return student; });

	// Last
	std::cout << reduce(foreach(map(filter(read<Student>(), [&](Student& student) ->bool {return student.xp >= xp; }),
		[&](Student& student)->Student { student.semester += 1; return student; }),
		[&](Student student) {std::cout << student << std::endl; }),
		[&](int x, Student& student) ->int {if (student.xp >= xp) return x + 1; else { std::cout << "algorithm error"; } return 0; }, 0);



	//for (auto s : students) {
	//	std::cout << s << std::endl;
	//}
	//std::cout << students.size() << std::endl;
	return 0;
}

/*
input:
  75 Hermann 3 80 Ronja 4 20 Beat 3 77 Sonja 4 90
expected output:
  name = Hermann semester= 4 xp= 80
  name = Beat semester= 4 xp= 77
  name = Sonja semester= 5 xp= 90
  3
*/


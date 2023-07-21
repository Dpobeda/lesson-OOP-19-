#include <iostream>
#include <vector>

#include <map>
#include <set>
#include <unordered_set> // Позволяет работать со структурамиу у которых есть 

#include <algorithm>

struct Record
{
	int id;
	std::string name;
	double vage;

	// Такой варинт - считается плохим, так как провоцирует непревиденные поведения.
	bool operator <(const Record& obj)const
	{
		return id < obj.id;
	}
	
	bool operator==(const Record& obj)const
	{
		return id == obj.id && name == obj.name && vage == obj.vage;
	}

};

namespace std 
{
	template<>
	struct hash <Record> // Позволяет создать уникальный слепок функций.
	{
		size_t operator()(const Record& obj) const
		{
			// Взять хэш функцию от первого поля. 
			// Сдвинуть результат на 1 бит влево.
			// Взять кэш функцию от второго поля.
			// Побитовое исключающие или между результатом и последней кэш функцией.

			using std::size_t;
			using std::hash;
			return (hash <size_t> () (obj.id)) ^ 
				   (hash <std::string> () (obj.name) << 1) ^ 
				   (hash <double> () (obj.vage) << 1);
		}
	};
}

void fO0() {
	std::unordered_set <Record> col1;
	col1.insert(Record());
	std::map <int, Record> col2;
	Record a{ 1 , "Vova", 56034.6 };
	col2.insert(std::pair <int, Record> (a.id, a));


}

int main()
{
	setlocale(LC_ALL, "Russian");

	std::vector <int> data;
	data.reserve(10'000); // Резервиуем 10000. Хорошо подходит, зная сколько нам нужно.
	// data.push_back(067);

	for (size_t i = 0; i < data.capacity(); i++) // Чтобы напичкать туда числами.
	{
		data.emplace_back(::rand() % 10'000); // emplace_back - создаёт новый объект на основе входных данных.
	}
	
	// Цикл прохода по массиву. 0(n).
	// Цикл поиска повторений. 0(n).
	// Изменение счётчика уникальных элетементов.
	
	std::set <int> uniq_elemets;
	
	for (size_t i = 0; i < data.size(); i++)
	{
		uniq_elemets.insert(data[i]);
	}
	
	std::cout << data.size() << " all data\n" << 
		 uniq_elemets.size() << " different data\n";

	std::vector <int> uniq_data;
	for (auto &el : data)
	{
		auto find = std::find(uniq_data.begin(), uniq_data.end(), el);
		if (find == uniq_data.end())
		{
			uniq_data.push_back(el);
		}
	}// n(n*n)
	
	std::cout << std::endl;

	std::cout << data.size() << " all data\n" <<
		uniq_data.size() << " different data\n";

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	std::cout << std::endl;

	std::vector <int> data_other;
	data_other.reserve(10'000);

	for (size_t i = 0; i < data_other.capacity(); i++) // Чтобы напичкать туда числами.
	{
		data_other.emplace_back(-5000 + ::rand() % 10'000);
	}
	
	std::set <int> uniq_elemets_other;

	for (size_t i = 0; i < data_other.capacity(); i++)
	{
		uniq_elemets_other.insert(data_other[i]);
	}

	std::cout << data_other.size() << " all other data\n" <<
		uniq_elemets_other.size() << " different other data\n";


	std::vector <int> result;
	std::set_intersection(uniq_elemets.begin(), // set_intersection - Они принимают коллекцию которые обрабатывают.
						  uniq_elemets.end(),
						  uniq_elemets_other.begin(), 
		                  uniq_elemets_other.end(),
						  std::back_inserter(result) // back_inserter - настраиваются на определёный контейнер в который они будут складывать.
		                  );
	
	std::cout << "\n";
	std::cout << result.size() << " intersect volume\n";

	return {};
}


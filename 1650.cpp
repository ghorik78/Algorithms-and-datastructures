#include <map>
#include <iostream>
#include <string>
#include <set>
#include <unordered_map>

using namespace std;

int main() {
	unordered_map<string, long long> cityAndMoney;		// Город и его деньги
	unordered_map<string, long long> richmanAndMoney; 	// Миллиардер и его сумма денег
	unordered_map<string, string> richmanAndCity; 		// Миллиардер и его местоположение
	map<long long, set<string>> moneyAndCitiesSet;		// Деньги и города, с такой суммой
	map<string, int> citiesRank;						// Финальный топ городов
	long long money;
	string name, city;
	int n;
	cin >> n;

    /* Читаем данные, заполяя соответствующие мапы */
	for (int i = 0; i < n; i++) {
		cin >> name >> city >> money;
		richmanAndMoney[name] = money;	// Богач-Деньги
		richmanAndCity[name] = city;	// Богач-Город

        /* Если город существует, значит он уже был ранее и его капитализация изменится. Тогда удаляем. */
		if (cityAndMoney.find(city) != cityAndMoney.end()) {
			long long sum = cityAndMoney[city]; 
			moneyAndCitiesSet[sum].erase(city);

			/* Если города с такой капитализацией перестали существовать, отчистим и ячейку с множеством городов. */
			if (moneyAndCitiesSet[sum].size() == 0) moneyAndCitiesSet.erase(sum);	
		}
		cityAndMoney[city] += money; //увеличение капитализации города
		moneyAndCitiesSet[cityAndMoney[city]].insert(city); //заносим город в множество городов с такой капитализацией
	}
	int days, movements, day, prevDay, currDay = 0;
	cin >> days >> movements;

    /* Вычисляем капитализацию в зависимости от дня */
	for (int i = 0; i <= movements; i++) {
		prevDay = currDay;
		// Обрабатываем ситуацию последнего дня, когда ещё нужно менять параметры сущностей, но данные вводить уже не надо.
		if (i == movements) day = days; 
		else cin >> day >> name >> city;
		currDay = day;
		map<long long, set<string>>:: reverse_iterator it = moneyAndCitiesSet.rbegin();
		/*
		Если в отсортированном по ключам контейнере {Деньги-Список городов} в ячейке, соответствующей наибольшему ключу 
		только один элемент в {set<string>}, значит сейчас существует единственный город с максимальной суммой, и ему 
		нужно добавить дни в карту {Город-Количество дней в топе}.
		*/
		if (currDay != prevDay && it->second.size() == 1) citiesRank[*(it->second.begin())] += currDay - prevDay;
		if (i < movements) {
			/* Прошлое местоположение. Если уехал - меняем информацию. */
			string oldLocation = richmanAndCity[name];
			long long oldMoney = cityAndMoney[oldLocation];
			moneyAndCitiesSet[oldMoney].erase(oldLocation);
			if (moneyAndCitiesSet[oldMoney].size() == 0) moneyAndCitiesSet.erase(oldMoney);
			cityAndMoney[oldLocation] -= richmanAndMoney[name];
			moneyAndCitiesSet[cityAndMoney[oldLocation]].insert(oldLocation);
            
			/* Новое местоположение. Аналогично обновляем всю инфу. */
			long long newMoney = cityAndMoney[city];
			moneyAndCitiesSet[newMoney].erase(city);
			if(moneyAndCitiesSet[newMoney].size() == 0) moneyAndCitiesSet.erase(newMoney);
			cityAndMoney[city] += richmanAndMoney[name];
			moneyAndCitiesSet[cityAndMoney[city]].insert(city);
			richmanAndCity[name] = city;
		}
	}
	for (const auto& c: citiesRank) cout << c.first << " " << c.second << endl; //вывод топа городов
   	return 0;
}

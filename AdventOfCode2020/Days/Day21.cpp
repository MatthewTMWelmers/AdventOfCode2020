#include <vector>
#include <string>
#include <map>

#include "../Core/Util.h"

std::map<std::string, std::vector<std::string>> getIngredientAllergies(std::vector<std::string> inputs) {
	std::map<std::string, std::vector<std::string>> ingredientAllergies;

	for (std::string input : inputs) {
		std::vector<std::string> listed = split<std::string>(input, " ");
		int splitPoint = indexOf<std::string>(listed, "(contains");

		std::vector<std::string> ingredients(listed.begin(), listed.begin() + splitPoint);
		std::vector<std::string> allergens(listed.begin() + splitPoint + 1, listed.end());
		for (size_t i = 0; i < allergens.size(); i++) {
			allergens[i].erase(allergens[i].end() - 1);
		}

		for (std::string ingredient : ingredients) {
			if (!ingredientAllergies.count(ingredient)) {
				ingredientAllergies[ingredient] = std::vector<std::string>();
			}

			for (std::string allergen : allergens) {
				if (indexOf(ingredientAllergies[ingredient], allergen) == -1) {
					ingredientAllergies[ingredient].push_back(allergen);
				}
			}
		}
	}

	for (std::string input : inputs) {
		std::vector<std::string> listed = split<std::string>(input, " ");
		int splitPoint = indexOf<std::string>(listed, "(contains");

		std::vector<std::string> ingredients(listed.begin(), listed.begin() + splitPoint);
		std::vector<std::string> allergens(listed.begin() + splitPoint + 1, listed.end());
		for (size_t i = 0; i < allergens.size(); i++) {
			allergens[i].erase(allergens[i].end() - 1);
		}

		for (std::string allergen : allergens) {
			for (std::pair<std::string, std::vector<std::string>> ingredientAllergy : ingredientAllergies) {
				if (indexOf(ingredients, ingredientAllergy.first) != -1) {
					continue;
				}

				std::vector<std::string> allergensForIngredient = ingredientAllergy.second;
				int index = indexOf(allergensForIngredient, allergen);
				if (index != -1) {
					allergensForIngredient.erase(allergensForIngredient.begin() + index);
				}

				ingredientAllergies[ingredientAllergy.first] = allergensForIngredient;
			}
		}
	}

	return ingredientAllergies;
}

int day21star1(std::vector<std::string> inputs) {
	std::map<std::string, std::vector<std::string>> ingredientAllergies = getIngredientAllergies(inputs);

	int nonAllergenic = 0;
	for (std::string input : inputs) {
		std::vector<std::string> listed = split<std::string>(input, " ");
		int splitPoint = indexOf<std::string>(listed, "(contains");

		for (std::string ingredient : std::vector<std::string>(listed.begin(), listed.begin() + splitPoint)) {
			if (ingredientAllergies[ingredient].empty()) {
				nonAllergenic++;
			}
		}

	}
	

	return nonAllergenic;
}

std::string day21star2(std::vector<std::string> inputs) {
	std::map<std::string, std::vector<std::string>> ingredientAllergies = getIngredientAllergies(inputs);
	std::vector<std::pair<std::string, std::vector<std::string>>> ingredientAllergens;

	std::copy_if(ingredientAllergies.begin(), ingredientAllergies.end(), back_inserter(ingredientAllergens), [](auto kv) -> int{ return !kv.second.empty(); });

	while (!all<std::pair<std::string, std::vector<std::string>>>(ingredientAllergens, [](std::pair<std::string, std::vector<std::string>> kv) -> int { return kv.second.size() == 1; })) {
		for (size_t i = 0; i < ingredientAllergens.size(); i++) {
			if (ingredientAllergens[i].second.size() == 1) {
				for (size_t j = 0; j < ingredientAllergens.size(); j++) {
					if (i == j) continue;
					int idx = indexOf(ingredientAllergens[j].second, ingredientAllergens[i].second[0]);
					if (idx != -1) {
						ingredientAllergens[j].second.erase(ingredientAllergens[j].second.begin() + idx);
					}
				}
			}
		}
	}

	std::sort(ingredientAllergens.begin(), ingredientAllergens.end(), [](auto a, auto b) -> int { return a.second[0] < b.second[0]; });

	std::string result = "";
	for (std::pair<std::string, std::vector<std::string>> allergen : ingredientAllergens) {
		if (result.length() != 0) result += ",";
		result += allergen.first;
	}

	return result;
}
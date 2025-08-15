#include <string>
#include <utility>

enum c_status {Friendly = 1, Neutral, Enemy};

class city {
    private:
        std::string country; // Country code (3 letters, uppercase)
        std::pair<int, int> coordinates;
        c_status city_status;
        int spy_count;

    public:
        // Default constructor
        city();

        // Constructor with parameters
        city(const std::string& c, const std::pair<int, int>& coord, const std::string& status, int spies);

        // Getter and Setter
        std::string get_country() const;
        void set_country(const std::string& newCountry);

        std::pair<int, int> get_coordinates() const;
        void set_coordinates(const std::pair<int, int>& newCoordinates);

        int get_city_status_int() const;
        std::string get_city_status_str() const;
        void set_city_status(const std::string& newCity_status);

        int get_spy_count() const;
        void set_spy_count(const int& newSpy_count);
};
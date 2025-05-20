namespace cpump_Lib {
  
    class __Base__ {
    	public: private: friend class Bombs; protected:
        struct PumpData { uint8_t pin; bool state; } _pump_;
        
        __Base__(uint8_t pin, bool state): _pump_{pin, state}
        {
            pinMode(_pump_.pin, OUTPUT);
            digitalWrite(_pump_.pin, _pump_.state);
        }

        virtual ~__Base__(void) 
        {
            pinMode(_pump_.pin, INPUT);
          	digitalWrite(_pump_.pin, LOW);
        }
      
        virtual void swapState(bool toChange = 0) = 0;
        virtual void analogPower(uint8_t value) = 0;
        bool getState() const { return (*this)._pump_.state; }
    };
  
  	inline namespace ScopeInternal {

    	class Bombs final: public __Base__ {
    	private:
        	uint8_t power;
    	public: using __Base__::getState;
          friend class __Base__;
        	explicit 
          		Bombs(uint8_t pin, bool state, uint8_t powerLevel = 0)
              	: __Base__(pin, state), power(powerLevel) {}

        	void swapState(bool toChange = 0x00) override {
            		(*this)._pump_.state ^= !toChange;
            		digitalWrite(_pump_.pin, _pump_.state);
        	}

        	void analogPower(uint8_t value = 0x00) override {
            		power = (value & ~(0b00000000));
            		analogWrite(_pump_.pin, power);
        	}

        	Bombs& operator+=(uint8_t &&value) {
           		power = (power + (value & 0xFF)) & 0xFF;
           	 	analogWrite((*this)._pump_.pin, this->power);
            		return *(this);
        	}

        	Bombs& operator-=(uint8_t &&value) {
            		power = (power - (value & 0xFF)) & 0xFF;
            		analogWrite((*this)._pump_.pin, this->power);
            		return *(this);
        	}

		Bombs& operator |=(uint8_t &&value) {
            		power |= (value & ~(0b0000000));
            		analogWrite((*this)._pump_.pin, this->power);
            		return *(this);
        	}

		Bombs& operator ++(uint8_t &&value) {
            		++ power; analogWrite((*this)._pump_.pin, this->power &0xff);
            		return *(this);
        	}

		Bombs& operator --(uint8_t &&value) {
            		-- power; analogWrite((*this)._pump_.pin, this->power &0xff);
            		return *(this);
        	}

		Bombs& operator =(const char* ASCII) {
			int powerL{0};
			for (auto i{}; i < strlen(ASCII); ++i) powerL += ASCII[i];
			powerL -= (powerL > 0xff) ? 0xAA : 0x00;
            		analogWrite((*this)._pump_.pin, powerL);
            		return *(this);
        	}

        	~Bombs(void) = default;
    	};
    };
}; // namespace cpump_Lib
using jobBomb = cpump_Lib::Bombs;

inline auto nxor = [](int x, int y) -> signed int
{ return ~(x ^ y)& ((!0) >> 0); };

decltype(auto) obj{ new jobBomb(0x03, (nxor(0, 1) & !0)) };

		void setup(void) noexcept(0)
		   
          		 {return;};

		void loop(void) noexcept(0)
{
    	(*obj += (uint8_t)('@'|'$'));
  	delay(0xFAu << 02 >> !0);
  	(*obj -= (uint8_t)('@'|'$'));
  	delay(0xFA << 02 >> !0);
    obj->swapState();
    delay(0xFAu << 02 >> !0);
          
};

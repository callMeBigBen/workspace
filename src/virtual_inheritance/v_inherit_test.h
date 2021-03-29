class Base {
public:
    int base_int;
    virtual int r_ret(){
        return 1;
    }
};

class Derived_A : public Base{
public:
    virtual int r_ret() override{
        return 2;
    };
};

class Derived_B : public Base{

};

class Derived_C final: public Derived_A, public Derived_B{
    
};
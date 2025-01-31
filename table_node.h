#pragma once
#include <iostream>

template<typename T>
class Table_Node{
private:
    struct Node{
        T* data_; 

        Node* top_;
        Node* right_;
        Node* bottom_;
        Node* left_;

        Node() : data_(nullptr), top_(nullptr),right_(nullptr), bottom_(nullptr), left_(nullptr) {}
    };

    Node* zero_point_;
    size_t size_x_;
    size_t size_y_;
    T* default_value_;

    void create_first(){
        zero_point_ = new Node();
        ++size_x_;
        ++size_y_;
    }

public:
    Table_Node(T default_value) : 
        zero_point_(nullptr), 
        size_x_(0), 
        size_y_(0) ,
        default_value_(new T(default_value))
    {}

    Table_Node(size_t x, size_t y, T default_value) : 
        zero_point_(nullptr), 
        size_x_(0), 
        size_y_(0) ,
        default_value_(new T(default_value))
    {
        for(size_t _x=0; _x<x; ++_x){
            add_right_border();
        }
        for(size_t _y=0; _y<y-1; ++_y){
            add_bottom_border();
        }
    }
    
    ~Table_Node(){
        Node* x_table = zero_point_;
        Node* y_table;
        Node* t;
        
        for(uint16_t x=0; x<size_x_; ++x){
            y_table = x_table;
            x_table = x_table->right_;
            
            for(uint16_t y=0; y<size_y_; ++y){
                t = y_table;
                y_table = y_table->bottom_;

                t->data_ = nullptr;
                t->top_ = nullptr;
                t->right_ = nullptr;
                t->bottom_ = nullptr;
                t->left_ = nullptr;

                delete t->data_;
                delete t;
            }
        }

        delete default_value_;
        default_value_ = nullptr;
        zero_point_ = nullptr;
    }

    inline bool empty(){
        return (zero_point_ == nullptr);
    }

    const T& get_width(){
        return size_x_;
    }

    const T& get_height(){
        return size_y_;
    }

    void add_top_border(){
        if(empty()){
            create_first();
            return;
        } 

        Node* t_bottom_ = zero_point_;
        zero_point_ = new Node();
        zero_point_->bottom_ = t_bottom_;
        t_bottom_->top_ = zero_point_;

        Node* t = zero_point_;
        Node* t_old;

        for(size_t x=1; x<size_x_; ++x){
            t->right_ = new Node();
            
            t_old = t;
            t = t->right_;
            t->left_ = t_old;
            
            t_bottom_ = t_bottom_->right_;
            t->bottom_ = t_bottom_;
            t_bottom_->top_ = t;
        }

        ++size_y_;
    }

    void add_right_border(){
        if(empty()){
            create_first();
            return;
        } 

        Node* t = zero_point_;
        Node* t_top_;
        Node* t_right_;

        for(size_t x=0; x<size_x_-1; ++x){
            t = t->right_;
        }

        t->right_ = new Node();
        t_right_ = t->right_;
        t_right_->left_ = t;

        for(uint16_t y=0; y<size_y_-1; ++y){
            t_top_ = t->right_;
            t = t->bottom_;

            t->right_ = new Node();
            t_right_ = t->right_;
            t_right_->left_ = t;
            t_right_->top_ = t_top_;
            t_top_->bottom_ = t_right_;
        }

        ++size_x_;
    }

    void add_bottom_border(){
        if(empty()){
            create_first();
            return;
        } 

        Node* t = zero_point_;
        Node* t_left_;
        Node* t_bottom_;

        for(size_t y=0; y<size_y_-1; ++y){
            t = t->bottom_;
        }

        t->bottom_ = new Node();
        t_bottom_ = t->bottom_;
        t_bottom_->top_ = t;

        for(uint16_t x=0; x<size_x_-1; ++x){
            t_left_ = t->bottom_;
            t = t->right_;

            t->bottom_ = new Node();
            t_bottom_ = t->bottom_;
            t_bottom_->top_ = t;
            t_bottom_->left_ = t_left_;
            t_left_->right_ = t_bottom_;
        }

        ++size_y_;
    }

    void add_left_border(){
        if(empty()){
            create_first();
            return;
        } 

        Node* t_right_ = zero_point_;
        zero_point_ = new Node();
        zero_point_->right_ = t_right_;
        t_right_->left_ = zero_point_;

        Node* t = zero_point_;
        Node* t_old;

        for(size_t y=1; y<size_y_; ++y){
            t->bottom_ = new Node();

            t_old = t;
            t = t->bottom_;
            t->top_ = t_old;
            
            t_right_ = t_right_->bottom_;
            t->right_ = t_right_;
            t_right_->left_ = t;
        }

        ++size_x_;
    }


    void delete_top_border(){
        if(empty()){
            std::cerr<<"Error: table is empty\n";
            return;
        }

        Node* t = zero_point_;
        Node* t_old;
        zero_point_ = zero_point_->bottom_;

        for(int x=0; x<size_x_; ++x){
            t_old = t;
            t_old->bottom_->top_ = nullptr;
            t = t->right_;

            t_old->data_ = nullptr;
            t_old->top_ = nullptr;
            t_old->right_ = nullptr;
            t_old->bottom_ = nullptr;
            t_old->left_ = nullptr;

            delete t_old->data_;
            delete t_old;
        }

        --size_y_;

        if(empty()){
            size_x_ = 0;
        }
    }

    void delete_right_border(){
        if(empty()){
            std::cerr<<"Error: table is empty\n";
            return;
        }

        Node* t = zero_point_;
        Node* t_old;

        for(int x=0; x<size_x_-1; ++x){
            t = t->right_;
        }

        for(int y=0; y<size_y_-1; ++y){
            t_old = t;
            t = t->bottom_;
            t_old->left_->right_ = nullptr;

            t_old->data_ = nullptr;
            t_old->top_ = nullptr;
            t_old->right_ = nullptr;
            t_old->bottom_ = nullptr;
            t_old->left_ = nullptr;

            delete t_old->data_;
            delete t_old;
        }

        --size_x_;

        if(empty() || size_x_ == 0){
            zero_point_ = nullptr;
            size_y_ = 0;
        }
    }

    void delete_bottom_border(){
        if(empty()){
            std::cerr<<"Error: table is empty\n";
            return;
        }

        Node* t = zero_point_;
        Node* t_old;

        for(int y=0; y<size_y_-1; ++y){
            t = t->bottom_;
        }

        for(int x=0; x<size_x_-1; ++x){
            t_old = t;
            t_old->bottom_->top_ = nullptr;
            t = t->right_;

            t_old->data_ = nullptr;
            t_old->top_ = nullptr;
            t_old->right_ = nullptr;
            t_old->bottom_ = nullptr;
            t_old->left_ = nullptr;

            delete t_old->data_;
            delete t_old;
        }

        --size_y_;

        if(empty() || size_y_ == 0){
            zero_point_ = nullptr;
            size_x_ = 0;
        }
    }

    void delete_left_border(){
        if(empty()){
            std::cerr<<"Error: table is empty\n";
            return;
        }

        Node* t = zero_point_;
        Node* t_old;
        zero_point_ = zero_point_->right_;

        for(int y=0; y<size_y_; ++y){
            t_old = t;
            t_old->right_->left_ = nullptr;
            t = t->bottom_;

            t_old->data_ = nullptr;
            t_old->top_ = nullptr;
            t_old->right_ = nullptr;
            t_old->bottom_ = nullptr;
            t_old->left_ = nullptr;

            delete t_old->data_;
            delete t_old;
        }

        --size_x_;

        if(empty()){
            size_y_ = 0;
        }
    }


    void print_table(){
        Node* t_old = zero_point_;
        Node* t;

        std::cout<<"size_x_: "<<size_x_<<" size_y_: "<<size_y_<<'\n';

        for(size_t y=0; y<size_y_; ++y){
            t = t_old;
            for(size_t x=0; x<size_x_; ++x){
                // std::cout<<'['<<x<<','<<y<<"] "<<(t->data_==nullptr ? *default_value_ : t->data_)<<" : "<<(t->top_==nullptr ? 0 : t->top_)<<' '<<(t->right_==nullptr ? 0 : t->right_)<<' '<<(t->bottom_==nullptr ? 0 : t->bottom_)<<' '<<(t->left_==nullptr ? 0 : t->left_)<<'\n';
                std::cout<<'['<<x<<','<<y<<"] "<<(t->data_==nullptr ? *default_value_ : *t->data_)<<" : "<<t->top_<<' '<<t->right_<<' '<<t->bottom_<<' '<<t->left_<<'\n';
                t = t->right_;
            }
            t_old = t_old->bottom_;
        }
    }

    void set_data(const size_t& x, const size_t& y, const T& data){
        if(x < 0 || x >= size_x_ || y < 0 || y >= size_y_){
            std::cerr << "Error: Out of bounds\n";
            return;
        }

        Node* t = zero_point_;

        for(size_t _x=0; _x<x; ++_x){
            t = t->right_;
        }

        for(size_t _y=0; _y<y; ++_y){
            t = t->bottom_;
        }

        t->data_ = new T(data);
    }

    const T& get_data_(const size_t& x, const size_t& y){
        if(x < 0 || x >= size_x_ || y < 0 || y >= size_y_){
            std::cerr << "Error: Out of bounds\n";
            return *default_value_;
        }

        Node* t = zero_point_;

        for(size_t _x=0; _x<x; ++_x){
            t = t->right_;
        }

        for(size_t _y=0; _y<y; ++_y){
            t = t->bottom_;
        }

        if(t->data_ == nullptr){
            std::cerr << "Error: Data not initialized\n";
            return *default_value_;
        }

        return *t->data_;
    }
};

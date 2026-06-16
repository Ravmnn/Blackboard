#pragma once




namespace bb
{




class Initializable
{
private:
    bool initialized_ = false;


public:
    virtual void initialize() noexcept { initialized_ = true; }

    void initialize_if_uninitialized() noexcept
    {
        if (!initialized_)
            initialize();
    }


    [[nodiscard]] bool initialized() const noexcept { return initialized_; }
};




}
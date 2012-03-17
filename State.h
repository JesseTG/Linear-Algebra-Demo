#ifndef STATE_H
#define STATE_H

class State
{
  public:
    virtual ~State() = 0;
    
    StateName getNextState() const { return nextstate; }
    virtual void input() = 0;
    virtual void logic() = 0;
    virtual void render() = 0;
    
    
    
  protected:
    StateName nextstate;
  
  private:
};

#endif //STATE_H

#ifndef STATE_H
#define STATE_H

class State
{
  public:
    virtual State() = 0;
    virtual ~State() = 0;
    
    
    void input() = 0;
    void logic() = 0;
    void render() = 0;
    
    
  protected:
  
  private:
}

#endif //STATE_H

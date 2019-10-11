#include <iostream>
#include <stdio.h>

static void DRAW(float x, float y){

}

class Particle {
private:
    float x,y,vx,vy,life;
    bool active;
public:
    Particle():active(false){

    }

    bool isActive(){return active;}

    //init particle data and set active
    void init(float x, float y, float vx, float vy, int life){
        this->x=x;
        this->y=y;
        this->vx=vx;
        this->vy=vy;
        this->life=life;
        this->active=true;
    }

    //update position of particle based on velocity
    void update(){
        this->x+=vx;
        this->y+=vy;
        life--;
        active=life>0;

    };

    //
    void draw(){
        DRAW(x,y);
        printf("\n[p %f %f]",x,y);

    };
};

class PooledParticleSystem {

private:
    static const int PARTICLES_COUNT=20;
    Particle particles[PARTICLES_COUNT];

public:
    PooledParticleSystem(){
    }

    void create(float x, float y, float velocity_x, float velocity_y, int life){

        Particle *particle=NULL;

        //lets find  a inactive partivle to use
        for(int i=0;i<PARTICLES_COUNT;i++){

            if(particles[i].isActive()== false){
                particle=&particles[i];
                break;
            }
        }

        if(particle==NULL){

            printf("NO MORE PARTICLES IN POOL!");
            return;
        }

        //initialize the partcle and set active
        particle->init(x,y,velocity_x,velocity_y,life);




    };

    void update(){

        for(int i=0;i<PARTICLES_COUNT;i++){
            if(particles[i].isActive()== true){
                particles[i].update();
            }
        }
    };

    void draw(){

        for(int i=0;i<PARTICLES_COUNT;i++){
            if(particles[i].isActive()== true){
                particles[i].draw();
            }
        }

    };
};

Particle create(){
     Particle p=new ;
     p.init(0,0,0,1,5);
    //p.draw();
//
  //  Particle *P2=new Particle();
//    delete p2;
    return p;
}

int main() {

    int FRAMES=10;

    Particle p=create();

     PooledParticleSystem *ps=new PooledParticleSystem();//hit
     //PooledParticleSystem ps; //stack;

    ps->create(0,0,0,1,10);
    for(int i=0;i<FRAMES;i++){
        printf("\n\n[FRAME %d]",i);
        ps->update();
        ps->draw();

        ps->create(0,0,0,1,5);
        ps->create(0,0,0,1,5);
    }

    return 0;
}
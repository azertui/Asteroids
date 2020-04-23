#include <asteroid.h>

void Asteroid::draw(SDL_Renderer *renderer){
    if(size>0){
        add(npoints,points,pos);
        SDL_RenderDrawLinesF(renderer,points,npoints);
        SDL_RenderDrawLineF(renderer,points[npoints-1].x,points[npoints-1].y,points[0].x,points[0].y);
        sub(npoints,points,pos);
    }
}

/*
SDL_FPoint collisionPoint(SDL_Rect *r){
    SDL_Rect rect;
    SDL_EnclosePoints(points,npoints,r,&rect);
    return {rect.x+rect.w/2+rect.h/2,rect.y+rect.w/2+rect.h/2};
}
*/

void Asteroid::move(){
    //mise a jour de la vitesse
    vx+=ax;
    vy+=ay;
    if(vx>game->max_speed) vx=game->max_speed;
    else if(vx<-game->max_speed) vx=-game->max_speed;
    if(vy>game->max_speed) vy=game->max_speed;
    else if(vy<-game->max_speed) vy=-game->max_speed;
    //deplacement des points
    pos.x+=vx;
    pos.y+=vy;

    pos.x=adjust(pos.x,game->width);
    pos.y=adjust(pos.y,game->height);

    //Mise a jour de l'acceleration
    if(ax==0 || (ax<VOID_RESISTANCE && ax>-VOID_RESISTANCE)){
        ax=0;
        if(game->obstacle_slowing){
            if(vx<VOID_RESISTANCE && vx>-VOID_RESISTANCE){
                vx=0;
            }
            else
                vx>0?vx-=VOID_RESISTANCE:vx+=VOID_RESISTANCE;
        }
    }
    else if(ax<0)
        ax+=VOID_RESISTANCE;
    else
        ax-=VOID_RESISTANCE;
    if(ay==0 || (ay<VOID_RESISTANCE && ay >-VOID_RESISTANCE)){
        ay=0;
        if(game->obstacle_slowing){
            if(vy<VOID_RESISTANCE && vy>-VOID_RESISTANCE){
                vy=0;
            }
            else
                vy>0?vy-=VOID_RESISTANCE:vy+=VOID_RESISTANCE;
        }
    }
    else if(ay<0)
        ay+=VOID_RESISTANCE;
    else
        ay-=VOID_RESISTANCE;
}

/*  Arguments: 
    set of points describing the object (considering the position), 
    position of the object,
    number of points in the set
*/

bool Asteroid::checkObjectCollision(SDL_FPoint objPoints[], 
                              SDL_FPoint objPos, int n) {
    SDL_FRect objRect, obstRect;
    add(npoints, points, pos);
    SDL_EncloseFPoints(points,npoints,&obstRect);
    SDL_EncloseFPoints(objPoints,n,&objRect);
    if (!SDL_FRectHasIntersection(&objRect, &obstRect)) {
        // enclosing rectangles don't intersect
        // std::cout << "rectangles don't intersect" << std::endl;
        sub(npoints, points, pos);
        return false;
    } else {
        // enclosing rectangles intersect
        for (int i=0; i<npoints; i++) {
            for (int j=0; j<n; j++) {
                if (segmentsIntersect(points[i],points[(i+1)%npoints],
                                      objPoints[j],objPoints[(j+1)%n])) {
                    //std::cout << "sides intersect" << std::endl;
                    sub(npoints, points, pos);
                    return true;
                    }
            }
        }
        // no border lines intersect -- check if object is inside the obstacle
        for (int i=0; i<npoints; i++) {
            if (segmentsIntersect(points[i],points[(i+1)%npoints],
                                      pos,objPos)) {
                //std::cout << "center-center cross the obstacle" << std::endl;
                sub(npoints, points, pos);
                return false;
            }
        }
        //std::cout << "object inside the obstacle" << std::endl;
        sub(npoints, points, pos);
        return true;
    }
}

std::list<Obstacle*> Asteroid::split(){
    std::list<Obstacle*> result;
    if (size>1) {
        Asteroid* obs;
        for (int i=0; i<size; i++) {
            obs = new Asteroid(pos.x, pos.y, size-1, game);
		    result.emplace_front(obs);
        }
    }
    return result;

}

void Asteroid::generate(){
    vx=vy=ax=ay=0;
    npoints = 8 + (size-1)*4;
    float radius=static_cast <float> (size*15);
    float angl = 0;
    for(int k=0; k<npoints; k++){
        float r = radius * (0.75 + static_cast <float> (rand()) / 
                            (static_cast <float> (RAND_MAX)*2));
        float x = r * cosf(angl);
        float y = r * sinf(angl); 
        points[k]={x,y};
        angl += 2*M_PI/npoints;
    }
}

void Asteroid::init_movement(){
    double r=(double)rand()/RAND_MAX;
    ax=r*(game->initial_acc_max-game->initial_acc_min);
    if(rand()%2)
        ax=-ax;
    r=(double)rand()/RAND_MAX;
    ay=r*(game->initial_acc_max-game->initial_acc_min);
    if(rand()%2)
        ay=-ay;
}
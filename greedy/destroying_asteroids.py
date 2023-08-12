def asteroidsDestroyed(mass: int, asteroids: list[int]) -> bool:
    asteroids.sort()

    for asteroid in asteroids:
        if asteroid > mass:
            return False
        
        mass += asteroid
    
    return True
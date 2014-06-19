import flixel.FlxSprite;
import flixel.FlxG;
import flixel.effects.FlxFlicker;
import flixel.group.FlxGroup;


class Hero extends FlxSprite {
    private inline static var HERO_ACCEL: Float     = 100;
    private inline static var HERO_MAXVEL: Float    = 70;
    private inline static var HERO_DRAG: Float      = 100;
	private static inline var SHOTS_PER_SECOND = 3;     
    private static inline var BULLET_SPEED = 200;
	
    private var walking_front: Bool = true;
    public var energy(default, null): Int = 3;
	public var bullets: FlxGroup;
    private var timeToNextShoot: Float;
    

    public function new (X: Float = 0, Y: Float = 0){
        super(X, Y);
        loadGraphic("assets/images/sprites_alpha.png", true, 16, 16);
        animation.add("standing_front", [96], 1);
        animation.add("standing_back", [112], 1);
        animation.add("walking_front", [97, 98, 99], 5);
        animation.add("walking_back", [113, 114, 115], 5);
        animation.play("standing_front");
        maxVelocity.x = maxVelocity.y = HERO_MAXVEL;
        drag.x = drag.y = HERO_DRAG;
		bullets = new FlxGroup();
        timeToNextShoot = 0;
    }

    public override function update(): Void {
        super.update();
		 timeToNextShoot += FlxG.elapsed;
		
		
        if(FlxG.keys.pressed.A){
            animation.play("walking_front");
            acceleration.x = -HERO_ACCEL;
            walking_front = true;
        }else if(FlxG.keys.pressed.D){
            animation.play("walking_front");
            acceleration.x = HERO_ACCEL;
            walking_front = true;
        }else{
            acceleration.x = 0;
        }

        if(FlxG.keys.pressed.W){
            animation.play("walking_back");
            acceleration.y = -HERO_ACCEL;
            walking_front = false;
        }else if(FlxG.keys.pressed.S){
            animation.play("walking_front");
            acceleration.y = HERO_ACCEL;
            walking_front = true;
        }else{
            acceleration.y = 0;
        }
		
		if (FlxG.keys.pressed.SPACE && timeToNextShoot>=(1.0/SHOTS_PER_SECOND))
		{		
			 createNewBullet(); 
		}

        if(Math.abs(velocity.x) < 5 && Math.abs(velocity.y) < 5){
            if(walking_front)
                animation.play("standing_front");
            else
                animation.play("standing_back");
        }
    }
	
	private function createNewBullet()
    {
        var bullet: Bullet;
        // pedimos al grupo una bala que ya no se esté utilizando
        bullet = cast(bullets.recycle(Bullet), Bullet);
        // la revivimos y reposicionamos
        bullet.reset(x + this.width / 2.0 - bullet.width / 2.0, y);
		if (walking_front)
		{
			bullet.velocity.y = BULLET_SPEED;
		}
		else
		{
			bullet.velocity.y = -BULLET_SPEED;
		}        
		timeToNextShoot = 0;
    }

    // decrementa la energía del personaje y aplica el filtro de "flickering"
    public function receiveDamage()
    {
        // solo dañamos al personaje si no está parpadeando
        if(!FlxFlicker.isFlickering(this)){
            // aplica un filtro de flicker de 1 segundo
            FlxFlicker.flicker(this);
            energy -= 1;
        }
    }
}

package  
{
	import adobe.utils.CustomActions;
	import flash.display.BitmapData;
	import flash.sampler.NewObjectSample;
	import net.flashpunk.Entity;
	import net.flashpunk.Graphic;
	import net.flashpunk.graphics.Image;
	import net.flashpunk.masks.Pixelmask;
	import net.flashpunk.Sfx;
	import net.flashpunk.graphics.Emitter;
	import net.flashpunk.graphics.Graphiclist;
	import net.flashpunk.graphics.Spritemap;
	import net.flashpunk.utils.Key;
	import net.flashpunk.utils.Input;
	import net.flashpunk.FP;
	import net.flashpunk.Tween;
	import net.flashpunk.utils.Ease;
	
	/**
	 * ...
	 * @author ...
	 */
	public class Enemigo extends Entity 
	{
		[Embed(source="BubblePlop.mp3")]
		private	const HIT_SND:Class;		
		private	var	hitSfx:Sfx;
		
		[Embed(source="tortuga.png")]
		private const IMG:Class;
		private var sprite:Spritemap;
		
		private var exp_Emiter:Emitter;
		
		public var isDead:Boolean = false;
				
		private const SCALE = 1.0;
		private const VEL_X = 50;		
		private const VEL_Y = 500;
		private const VEL_Y_JUMP = 300;
		private const DIR_L = -1;
		private const DIR_R = 1;				
		private const DIR_NA = 0;
		private const GRAVEDAD = -800;
		private const FRICCION = 500;
				
		private const PISO_Y = 500;
		
		private var dir_x_f = 0;
		private var dir_x = 0;		
		private var vel_x = 0;
		private var vel_y = 0;	
		private var center_y = 0;
		private var angulo = 0;		
	
		private var hit:Boolean = false;
		private var grp_List:Graphiclist;
		
		public function Enemigo(px:Number = 0, py:Number = 0) 
		{				
			hitSfx = new Sfx(HIT_SND);	
			
			exp_Emiter = new Emitter(new BitmapData(4,4),4,4);
			exp_Emiter.newType("explode",[0]);			
			exp_Emiter.setMotion("explode", 0, 300, 1, 270, -40, -0.95);
			exp_Emiter.relative = false;
			
			sprite = new Spritemap(IMG,50, 38);		
			sprite.add("run", [0,1,2,3,4,5], 30, true);
			
			setHitbox(50, 38);
			width = 50
			height = 38;
			
			grp_List = new Graphiclist(sprite, exp_Emiter);
			
			super(px, py, grp_List);
			
			type = "enemigo";
			
			sprite.play("run");	
			
			dir_x = DIR_L;
			vel_x = VEL_X * dir_x*SCALE;			
		}
		
		override public function update():void
		{	
			if (x < 0)
			{
				var world:GameWorld = FP.world as GameWorld;						
				FP.world.remove(this);
			}
			
			move();

			if (isDead)
			{
				this.sprite.visible = false;
				if (exp_Emiter.particleCount == 0)
				{
					var world:GameWorld = FP.world as GameWorld;						
					FP.world.remove(this);
				}				
			}
			
			super.update();
		}
		
		private function move():void 
		{
			
			if(dir_x != DIR_NA)
			{
				x += vel_x * FP.elapsed;				
			}
			else if (vel_x != 0)
			{	
				vel_x += FRICCION * dir_x_f * FP.elapsed;					
				x += vel_x * FP.elapsed;
				
				if (vel_x > 0 && dir_x_f > 0 || vel_x < 0 && dir_x_f < 0)
				{
					vel_x = 0;
					dir_x_f = DIR_NA;					
				}
			}	
			
				
			if (vel_y > 0 || y < PISO_Y)
			{				
				vel_y += GRAVEDAD * FP.elapsed;	
				y += vel_y * FP.elapsed * -1;
			}
			
			if (y > PISO_Y)
			{
				y = PISO_Y;
				vel_y = 0;
			}
		
		}
		
		public function getWidth():Number
		{
			return (sprite.width / sprite.columns);
		}
		
		public function getHeight():Number
		{
			return (sprite.height / sprite.rows);
		}
		
		public function  die():void 
		{	
			if (!isDead)
			{
				isDead = true;
				this.collidable = false;	
				hitSfx.play();
				exp_Emiter.setColor("explode", 0xFFFFFF, 0xFFFFFF);
			
				for (var i:uint = 0; i < 100; i++)
				{
					exp_Emiter.emit("explode", x + width / 2, y + height / 2);
				}
			}
		}
		
	}
}

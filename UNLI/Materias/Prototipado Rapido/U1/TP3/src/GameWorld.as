package
{
	import net.flashpunk.graphics.Text;
	import net.flashpunk.World;
	import net.flashpunk.FP;
	
	public class GameWorld extends World
	{
		protected var player:Personaje;
		
		private var antigText:Text;
		
		public function GameWorld()
		{
			this.player = new Personaje(FP.screen.x + 100, FP.screen.height / 2);				
			this.add(player);
			antigText = new Text("prueba", 0, 0, 500, 100);
			this.addGraphic(antigText);
			
			
			var enemigo:Enemigo = new Enemigo(FP.screen.width / 2 - 150 , FP.screen.height / 2);			
			enemigo.SetOnJump();
			this.add(enemigo);
					
			enemigo = new Enemigo(FP.screen.width / 2 + 100, FP.screen.height / 2);
			enemigo.SetOnAntiG();
			this.add(enemigo);			
						
			enemigo = new Enemigo(FP.screen.width - 200, 0); 
			enemigo.SetOnFire();
			this.add(enemigo);
			
											
			this.add(new Solid(	FP.screen.width / 2 - 100 , 405));	
			this.add(new Solid(	FP.screen.width / 2 + 100 , 405));	
			
			this.add(new Solid(	FP.screen.width  - 200, 200));
			
		}
		
		override public function update():void
		{	
			var text:String = "[A] Left, [D] Right";
			
			if (player.CheckJump())
			{
				text += ", [W] Jump";
			}
			if (player.CheckFire())
			{
				text += "\n[SPACE] Fire";
			}			
			if (player.CheckMaxFire())
			{
				text += "\n[F] FireMax";
			}
			if (player.CheckAntiG())
			{
				text += "\n[SHIFT] Anti G -> " + player.GetAntiG().toString() + "%";
			}
			
			antigText.text = text;
			
			/*
			if (classCount(Enemy) < 10)
				for (var i:uint = 0; i < 10; i++)
					this.add(new Enemy(FP.rand(FP.screen.width - player.getWidth()), -(FP.rand(400) - player.getHeight())));
		    */
			
			super.update();						
		}
	}
}
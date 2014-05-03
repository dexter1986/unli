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
			
			this.add(new Enemigo(FP.screen.width / 2, FP.screen.height / 2));
			
			this.add(new Enemigo(FP.screen.width - 100, FP.screen.height / 2));
			
			this.add(new Enemigo(FP.screen.width - 200, FP.screen.height / 2));
			
			this.add(new Enemigo(FP.screen.width - 300, FP.screen.height / 2));
		}
		
		override public function update():void
		{	
			antigText.text = "Anti G -> " + player.GetAntiG().toString() + "%  [press SHIFT]\nNavigate: AWSD or Arrows -> Fire: SPACE";
			
			/*
			if (classCount(Enemy) < 10)
				for (var i:uint = 0; i < 10; i++)
					this.add(new Enemy(FP.rand(FP.screen.width - player.getWidth()), -(FP.rand(400) - player.getHeight())));
		    */
			
			super.update();						
		}
	}
}
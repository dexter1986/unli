package
{
	import adobe.utils.CustomActions;
	import net.flashpunk.graphics.Text;
	import net.flashpunk.World;
	import net.flashpunk.FP;
	
	public class GameWorld extends World
	{
		private var corazon:Corazon;
		private var escudo:Escudo;
		
		public function GameWorld()
		{			
			gameReboot();
		}
		
		override public function update():void
		{	
			super.update();						
		}
		
		public function gameReboot():void
		{
			this.corazon = new Corazon(FP.screen.width / 2, FP.screen.height / 2);
			this.corazon.x = FP.screen.width / 2 - this.corazon.getWidth() / 2;
			this.corazon.y = FP.screen.height / 2 - this.corazon.getHeight() / 2;
			this.add(corazon);
			
			this.escudo = new Escudo(FP.screen.width / 2, FP.screen.height / 2);
			this.escudo.x = FP.screen.width / 2 - this.escudo.getWidth() / 2;
			this.escudo.y = FP.screen.height / 2 - this.escudo.getHeight() / 2;
			this.escudo.Init();
			this.add(escudo);
		}
	}
}
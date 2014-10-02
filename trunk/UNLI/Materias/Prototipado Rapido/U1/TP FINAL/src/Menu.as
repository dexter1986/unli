package  
{
	import adobe.utils.CustomActions;
	import net.flashpunk.Entity;
	import net.flashpunk.graphics.Image;
	import net.flashpunk.FP;
	import net.flashpunk.masks.Pixelmask;
	import net.flashpunk.Sfx;
	import net.flashpunk.utils.Key;
	import net.flashpunk.utils.Input;
	import net.flashpunk.World;
	import net.flashpunk.tweens.misc.VarTween;
	import net.flashpunk.utils.Ease;
	import net.flashpunk.graphics.Text;
	/**
	 * ...
	 * @author Oscar Sanchez
	 */
	public class Menu extends World 
	{
		protected var status:String;
		protected var titleText:Text;
		protected var pressText:Text;
		private var titleTweenIn:VarTween;
		private var titleTweenOut:VarTween;
		private var pressTweenIn:VarTween;
		private var pressTweenOut:VarTween;
		
		
		public function Menu() 
		{
			CreateMenu();			
		}		
		
		public function CreateMenu():void
		{
			this.titleText = new Text("TRUE LIFE");
			this.pressText = new Text("Haz clic para continuar");
			
			this.titleText.color = 0xFFFFFF;
			this.titleText.scale = 2;
			this.pressText.color = 0xFFFFFF;
			this.pressText.alpha = 0;
			
			this.titleText.x = (FP.screen.width - this.titleText.scaledWidth) / 2;
			this.pressText.x = (FP.screen.width - this.pressText.width) / 2;
			
			this.titleText.y = -100;
			this.pressText.y = FP.screen.height * 0.75;
			
			titleTweenIn = new VarTween();
			titleTweenOut = new VarTween();
			pressTweenIn = new VarTween();
			pressTweenOut = new VarTween();
			
			this.addGraphic(titleText);
			this.addGraphic(pressText);			
			this.addTween(titleTweenIn);
			this.addTween(pressTweenIn);
			this.addTween(titleTweenOut);
			this.addTween(pressTweenOut);	
			
		}
		
		override public function begin():void
		{
			FP.screen.color = 0x000000;	
			this.status = "START";
		}
		
		override public function update():void
		{
			switch (status)
			{
				case "START": 
				{
					titleTweenIn.tween(titleText, "y", FP.screen.height * 0.25, 1, Ease.backOut);
					pressTweenIn.tween(pressText, "alpha", 1, 1);
					
					this.status = "WAIT1";
					break;
				}
				
				case "WAIT1":
				{
					if (titleTweenIn.percent == 1 && pressTweenIn.percent == 1)
					{
						this.status = "TO";
					}
				}
				
				case "TO": 
				{
					if (Input.mousePressed)
					{
						titleTweenOut.tween(titleText, "y", -100, 1, Ease.backIn);
						pressTweenOut.tween(pressText, "alpha", 0, 1);
						this.status = "WAIT2";
					}
					break;
				}
				
				case "WAIT2":
				{
					if (titleTweenOut.percent == 1 && pressTweenOut.percent == 1)
					{				
						this.status = "GAME";
						this.active = false;
					}					
				}
			}			
			super.update();			
		}
		
	}

}
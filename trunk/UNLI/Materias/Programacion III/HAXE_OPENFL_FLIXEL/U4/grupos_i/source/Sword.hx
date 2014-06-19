import flixel.FlxSprite;

class Sword extends FlxSprite
{
	public function new (X: Float = 0, Y: Float = 0){
    	super(X, Y);
        loadGraphic("assets/images/sprites_alpha.png", true, 16, 16);
        animation.frameIndex = 48;
    }
}
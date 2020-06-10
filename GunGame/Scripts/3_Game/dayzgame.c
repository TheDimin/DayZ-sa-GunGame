modded class DayZGame
{
	void DayZGame()
	{
		// register custom input from script (for debug + development)
		UAInput input1 = GetUApi().RegisterInput("UAScriptedInput1","Scripted_Input_1","core");

		// bind UAScriptedInput2 to key 'Ctrl + P'
		input1.BindCombo("kLControl");
		input1.BindCombo("kP");		
	}
};
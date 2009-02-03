#include <string>

class GFAudio
{
	/* SO THAT THE FRAMEWORK CAN ACCESS PROTECTED MEMBERS */
	friend class GameFramework;

	public:
		/* NULL OBJECT */
		static const GFAudio null;

		/* PUBLIC DESTRUCTOR */
		~GFAudio();

		/* CONSTANTS FOR AUDIO PLAYBACK */
		static const int STOP = 0;
		static const int PLAY = 1;
		static const int PAUSE = 2;

		/* PLAYBACK FUNCTIONS */
		void setPlayback(int);
		void stop();

		/* OVERLOADED OPERATORS */
		bool operator==(const GFAudio&);

		/* PRINT FUNCTION (FOR DEBUG) */
		friend std::ostream& operator<<(std::ostream&, GFAudio&);

	protected:
		/* PROTECTED CONSTRUCTOR */
		GFAudio(int);

	private:
		/* REFERENCE NUMBER FOR FRAMEWORK */
		int _ref;
};

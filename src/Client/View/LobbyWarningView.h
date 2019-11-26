#ifndef LOBBY_WARNING_VIEW_H
#define LOBBY_WARNING_VIEW_H

#include "ObjectView.h"

class LobbyWarningView : public ObjectView {
private:
	bool _show;
	int _showTimer;
public:
	LobbyWarningView(const SdlTexture& tex);
	virtual void drawAt(int x, int y) override;
	void show();
	bool showing();
 	virtual ~LobbyWarningView() {}
};

#endif // LOBBY_WARNING_VIEW_H

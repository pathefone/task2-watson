module("luci.controller.watson_controller", package.seeall)

function index()
	entry({"admin", "services", "watson_datasend"}, cbi("watson_model"), _("Watson Datasend"),105)
end

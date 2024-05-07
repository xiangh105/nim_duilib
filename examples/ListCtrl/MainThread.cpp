#include "MainThread.h"
#include "MainForm.h"

void WorkerThread::Init()
{
	::OleInitialize(NULL);
	nbase::ThreadManager::RegisterThread(m_threadID);
}

void WorkerThread::Cleanup()
{
	nbase::ThreadManager::UnregisterThread();
	::OleUninitialize();
}

void MainThread::Init()
{
	::OleInitialize(NULL);
	nbase::ThreadManager::RegisterThread(kThreadUI);

	//启动工作线程
	m_workerThread.reset(new WorkerThread(kThreadWorker, "WorkerThread"));
	m_workerThread->Start();

	// 获取资源路径，初始化全局参数
	std::wstring theme_dir = nbase::win32::GetCurrentModuleDirectory();

	// Debug 模式下使用本地文件夹作为资源
	ui::GlobalManager::Instance().Startup(theme_dir + L"resources\\");

	//创建主窗口
	MainForm* pWindow = new MainForm();
	pWindow->CreateWnd(NULL, L"ListCtrl控件测试程序", UI_WNDSTYLE_FRAME, WS_EX_LAYERED);
	pWindow->SetIcon(IDI_LISTCTRL);
	pWindow->CenterWindow();
	pWindow->ShowWindow();
}

void MainThread::Cleanup()
{
	ui::GlobalManager::Instance().Shutdown();
	if (m_workerThread != nullptr) {
		m_workerThread->Stop();
		m_workerThread.reset(nullptr);
	}
	SetThreadWasQuitProperly(true);
	nbase::ThreadManager::UnregisterThread();
	::OleUninitialize();
}

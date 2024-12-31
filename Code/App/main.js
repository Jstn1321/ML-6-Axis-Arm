const { app, BrowserWindow, ipcMain } = require('electron');
const { exec } = require('child_process');
const path = require('path');

const createWindow = () => {
  const win = new BrowserWindow({
    width: 800,
    height: 750,
    webPreferences: { 
      nodeIntegration: true,
      contextIsolation: false,
    },
  });

  win.loadFile('index.html');
};

ipcMain.on('takePic', (event) => {
  exec('cmd.exe /c "conda activate tf && python ./scripts/takePic.py"', (err, stdout, stderr) => {
    if (err) {
      console.error(`exec error: ${err}`);
      event.reply('console-message', `Error: ${stderr}`);
      return;
    }
    console.log(`stdout: ${stdout}`);
    event.reply('console-message', `${stdout}`);
    
    event.sender.send('update', path.join(__dirname, 'scripts/assets/takenPic/filename.jpg'));
  });
});

ipcMain.on('identify', (event) => {
  exec('cmd.exe /c "conda activate tf && python ./scripts/identify.py"', (err, stdout, stderr) => {
    if (err) {
      console.error(`exec error: ${err}`);
      event.reply('console-message', `Error: ${stderr}`);
      return;
    }
    console.log(`stdout: ${stdout}`);
    event.reply('console-message', `${stdout}`);
  });
});

ipcMain.on('sort', (event) => {
  exec('cmd.exe /c "conda activate tf && python ./scripts/sort.py"', (err, stdout, stderr) => {
    if (err) {
      console.error(`exec error: ${err}`);
      event.reply('console-message', `Error: ${stderr}`);
      return;
    }
    console.log(`stdout: ${stdout}`);
    event.reply('console-message', `${stdout}`);
  });
});

app.whenReady().then(() => {
  createWindow();

  app.on('activate', () => {
    if (BrowserWindow.getAllWindows().length === 0) {
      createWindow();
    }
  });
});

app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') {
    app.quit();
  }
});

const { app, BrowserWindow, ipcMain } = require('electron');
const { exec } = require('child_process');
const path = require('path');
const fs = require('fs');

const createWindow = () => {
  const win = new BrowserWindow({
    width: 800,
    height: 760,
    webPreferences: { 
      nodeIntegration: true,
      contextIsolation: false,
    },
  });

  win.loadFile('index.html');
};

ipcMain.on('takePic', (event) => {
  exec('cmd.exe /c "python ./scripts/takePic.py"', (err, stdout, stderr) => {
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
  exec('cmd.exe /c "python ./scripts/idYOLO.py"', (err, stdout, stderr) => {
    if (err) {
      console.error(`exec error: ${err}`);
      event.reply('console-message', `Error: ${stderr}`);
      return;
    }
    console.log(`stdout: ${stdout}`);
    event.reply('console-message', `${stdout}`);

    fs.readdir(path.join(__dirname, 'runs/detect/'), (err, files) => {
      var num = files.length;
      num = String(num);
      if (num == 0){
        num = "";
      }
      event.sender.send('update', path.join(__dirname, 'runs/detect/predict'+num+"/filename.jpg"));
    });
  });
})
ipcMain.on('sort', (event) => {
  exec('cmd.exe /c "python ./scripts/sortYOLO.py"', (err, stdout, stderr) => {
    if (err) {
      console.error(`exec error: ${err}`);
      event.reply('console-message', `Error: ${stderr}`);
      return;
    }
    console.log(`stdout: ${stdout}`);
    event.reply('console-message', `${stdout}`);
  });
});

ipcMain.on('auto', (event) => {
  exec('cmd.exe /c "python ./scripts/setAuto.py"', (err, stdout, stderr) => {
    if (err) {
      console.error(`exec error: ${err}`);
      event.reply('console-message', `Error: ${stderr}`);
      return;
    }
    console.log(`stdout: ${stdout}`);
    event.reply('console-message', `${stdout}`);
  });
});

ipcMain.on('manual', (event) => {
  exec('cmd.exe /c "python ./scripts/setManual.py"', (err, stdout, stderr) => {
    if (err) {
      console.error(`exec error: ${err}`);
      event.reply('console-message', `Error: ${stderr}`);
      return;
    }
    console.log(`stdout: ${stdout}`);
    event.reply('console-message', `${stdout}`);
  });
});

ipcMain.on('picsort', (event) => {
  exec('cmd.exe /c "python ./scripts/picandsort.py"', (err, stdout, stderr) => {
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
